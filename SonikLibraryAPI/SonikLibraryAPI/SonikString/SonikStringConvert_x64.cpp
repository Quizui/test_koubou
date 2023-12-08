/*
 * SonikStringConvert_x64.cpp
 *
 *  Created on: 2019/02/09
 *      Author: SONIK
 */

#ifdef __SONIK_x86_64__

#include <cstring>
#include <cstdlib>
#include <new>
#include <algorithm>
#include "locale.h"
#include "stdint.h"
#include "wchar.h"
#include "SonikStringConvert.h"
#include "../MathBit/MathBit.h"

namespace SonikConvStaticTable
{
	//UTF-8 FULLWIDKATAKANA => HALFWIDTH KATAKANA
	static const uint32_t HW_KANA_OFFSET_STARTPOINT[] = {0xE382A1, 0xE38380};
	//c:形式 => 左3Byte -> 実文字コード、 右1Byte -> 最上位bit = ポインタ進行数(0 or 1)  残り7bit = 下記配列の濁点位置。
	static const uint32_t HW_KANA[] = {0xEFBDA700, 0xEFBDB100, 0xEFBDA800, 0xEFBDB200, 0xEFBDA900, 0xEFBDB300, 0xEFBDAA00, 0xEFBDB400, 0xEFBDAB00, 0xEFBDB500,
									   	   	0xEFBDB600, 0xEFBDB69F, 0xEFBDB700, 0xEFBDB79F, 0xEFBDB800, 0xEFBDB89F, 0xEFBDB900, 0xEFBDB99F, 0xEFBDBA00, 0xEFBDBA9F,
											0xEFBDBB00, 0xEFBDBB9F, 0xEFBDBC00, 0xEFBDBC9F, 0xEFBDBD00, 0xEFBDBD9F, 0xEFBDBE00, 0xEFBDBE9F, 0xEFBDBF00, 0xEFBDBF9F,
											0xEFBE8000,
											0xEFBE9E00, 0xEFBE9F00, //c: <- ". ゜ 31 32
									  	  	0xEFBE809F, 0xEFBE8100, 0xEFBE819F, 0xEFBDAF00, 0xEFBE8200, 0xEFBE829F, 0xEFBE8300, 0xEFBE839F, 0xEFBE8400, 0xEFBE849F,
											0xEFBE8500, 0xEFBE8600, 0xEFBE8700, 0xEFBE8800, 0xEFBE8900,
											0xEFBE8A00, 0xEFBE8A9F, 0xEFBE8AA0, 0xEFBE8B00, 0xEFBE8B9F, 0xEFBE8BA0, 0xEFBE8C00, 0xEFBE8C9F, 0xEFBE8CA0, 0xEFBE8D00, 0xEFBE8D9F, 0xEFBE8DA0, 0xEFBE8E00, 0xEFBE8E9F, 0xEFBE8EA0,
											0xEFBE8F00, 0xEFBE9000, 0xEFBE9100, 0xEFBE9200, 0xEFBE9300,
											0xEFBDAC00, 0xEFBE9400, 0xEFBDAD00, 0xEFBE9500, 0xEFBDAE00, 0xEFBE9600,
											0xEFBE9700, 0xEFBE9800, 0xEFBE9900, 0xEFBE9A00, 0xEFBE9B00,
											0xE383AE00, 0xEFBE9C00, 0xE383B000, 0xE383B100, 0xEFBDA600, 0xEFBE9D00,
											0xEFB9F39F, 0xE383B500, 0xE383B600, 0xEFBE9C9F, 0xE383B800, 0xE383B900, 0xEFBDA69F,
										   };

};

//文字列のタイプをチェックします。
//完全な判別は不可能（らしい）なので可能性の範囲でチェックされた結果を返却します。
//2019/01/14 SJISの場合、utf-8が後ろに入っている場合もあるので、utf-8が出るまですべて読み込みます。
SonikLibConvertType SonikLibStringConvert::CheckConvertType(const char* pCheckSrc)
{
	SonikLibConvertType conv_t = SCHTYPE_UNKNOWN;

	if(pCheckSrc == 0)
	{
		return conv_t;
	};

	uint32_t Len = strlen(pCheckSrc);
	uint32_t lop = 0;
	unsigned char val;

	for(lop =0; lop < Len; ++lop)
	{
		val = pCheckSrc[lop];

		if(lop == 0 && Len > 3)
		{
			if(static_cast<unsigned char>(pCheckSrc[0]) == 0xEF
			   && static_cast<unsigned char>(pCheckSrc[1]) == 0xBB
			   && static_cast<unsigned char>(pCheckSrc[2]) == 0xBF
			)
			{
				//BOM付きUTF8
				conv_t = SCHTYPE_BOMUTF8;
				break;
			};
		};

		if( 0x01 <= val && val <= 0x7E )
		{
			//ASCIIなのでSJIS判定
			conv_t = SCHTYPE_SJIS;
			continue;
//			break;
		};

		if( 0x80 <= val && val<= 0x9F)
		{
			//SJIS判定確定
			conv_t = SCHTYPE_SJIS;
//			continue;
			break;
		};

		if( 0xC2 <= val && val <= 0xDF )
		{

			//半角文字かもしれないので設定した上で読み飛ばし  0xa0(0xa1)～0xdf
			if( 0xA0 <= val && val <= 0xDF )
			{
				conv_t = SCHTYPE_SJIS;
				continue;
			};

			if( (Len - (lop+1)) == 0 )
			{
				//ANSIなのでSJISともUTF8とも取れるので、UTF8として解釈
				conv_t = SCHTYPE_UTF8;
				break;
			};

			if( (Len - (lop+1)) < 2 )
			{
				//第２バイトにSJISの第１範囲が来ても最終文字なのでSJISの可能性は無い。UTF-8
				conv_t = SCHTYPE_UTF8;
				break;
			};

			if( 0x80 <= static_cast<unsigned char>(pCheckSrc[lop+1]) && static_cast<unsigned char>(pCheckSrc[lop+1]) <= 0x9F )
			{
				//SJIS第１かもしれないので予想としてSJISをセットして次へ
				conv_t = SCHTYPE_SJIS;

				if( 0xE0 <= static_cast<unsigned char>(pCheckSrc[lop+2]) && static_cast<unsigned char>(pCheckSrc[lop+2]) <= 0xEF )
				{
					//SJIS確定
					conv_t = SCHTYPE_SJIS;
					break;
				};

				++lop;
			};

			//全部違えばUTF-8
			conv_t = SCHTYPE_UTF8;
			break;
		};


		if( 0xE0 <= val && val <= 0xEF )
		{
			if(lop > 0 )
			{
				if( static_cast<unsigned char>(pCheckSrc[lop - 1]) >= 0x80 && static_cast<unsigned char>(pCheckSrc[lop - 1]) <= 0x9F )
				{
					//SJISの組み合わせ
					conv_t = SCHTYPE_SJIS;
					continue;
//					break;
				};
			};

			//可能性的にはUTF8の確率が高いため、UTF8と判断
			conv_t = SCHTYPE_UTF8;
			break;
		};



		if( 0xA0 <= val && val <= 0xC1 )
		{
			//SJIS判定
			conv_t = SCHTYPE_SJIS;
			continue;
//			break;
		};


		if( 0xF0 <= val && val <= 0xFD )
		{
			//UTF8確定
			conv_t = SCHTYPE_UTF8;
			break;
		};


		//その他よくわからない部分は読み飛ばし。
	};

	//返却
	return conv_t;
};

//文字列のタイプをチェックし、その文字列で使用されているバイト数を返却します。
//文字列のタイプチェックは可能性の範囲のチェックとなります。
//SJIS, UTF-8のみに対応。
uint64_t SonikLibStringConvert::GetStringLengthByte(const char* pCheckSrc)
{
	SonikLibConvertType Type_ = SonikLibStringConvert::CheckConvertType(pCheckSrc);
	uint64_t cnt = 0;

	if( Type_ == SCHTYPE_SJIS || Type_ == SCHTYPE_UTF8)
	{
		while( (*pCheckSrc) != 0 )
		{
			++cnt;
			++pCheckSrc;
		};

		return cnt;
	};

	//判定できなかったのでカウントできない。
	return 0;

};

//unicode文字の文字列バイト数を返却します。
uint64_t SonikLibStringConvert::GetStringLengthByte(const char16_t* pCheckSrc)
{
	uint64_t cnt = 0;

	while( (*pCheckSrc) != 0 )
	{
		cnt += 2;
		++pCheckSrc;
	};

	return cnt;
};

//unicode(UTF-32)文字の文字列バイト数を返却します。
//ただのループ。
uint64_t SonikLibStringConvert::GetStringLengthByte(const int32_t* pCheckSrc)
{
	uint64_t cnt_ = 0;

	while( (*pCheckSrc) != 0 )
	{
		cnt_ += 4;
		++pCheckSrc;
	};

	return cnt_;
};


//文字列のタイプをチェックし、その文字列で使用されている文字数を返却します。
//文字列のタイプチェックは可能性の範囲のチェックとなります。
//SJIS, UTF-8のみに対応。
uint64_t SonikLibStringConvert::GetStringCount(const char* pCheckSrc)
{
	SonikLibConvertType Type_ = SonikLibStringConvert::CheckConvertType(pCheckSrc);
	uint64_t cnt = 0;
	uint64_t bitcnt = 0;
	unsigned char swapbit = 0;

	if( Type_ == SCHTYPE_SJIS )
	{
		while( static_cast<unsigned char>((*pCheckSrc)) != 0x00 )
		{
			if( (0x80 <= static_cast<unsigned char>((*pCheckSrc)) && static_cast<unsigned char>((*pCheckSrc)) <= 0x9F) ||  (0xE0 <= static_cast<unsigned char>((*pCheckSrc)) && static_cast<unsigned char>((*pCheckSrc)) <= 0xFC) )
			{

//				++cnt;
				++pCheckSrc;
			};

			++cnt;
			++pCheckSrc;
		};

	}else if( Type_ == SCHTYPE_UTF8 )
	{
		while( static_cast<unsigned char>((*pCheckSrc)) != 0x00 )
		{
			swapbit = (*pCheckSrc);
			swapbit = SonikMathBit::BitSwapFor8bit(swapbit);

			bitcnt =  ~(swapbit);

			bitcnt |= (bitcnt << 1);
			bitcnt |= (bitcnt << 2);
			bitcnt |= (bitcnt << 4);
			bitcnt |= (bitcnt << 8);
			bitcnt |= (bitcnt << 16);
			bitcnt |= (bitcnt << 32);

//			bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
//			bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
//			bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
//			bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );
//
//			bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);

			bitcnt = (bitcnt & 0x5555555555555555) + ( (bitcnt >> 1) & 0x5555555555555555 );
			bitcnt = (bitcnt & 0x3333333333333333) + ( (bitcnt >> 2) & 0x3333333333333333 );
			bitcnt = (bitcnt & 0x0F0F0F0F0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F0F0F0F0F );
			bitcnt = (bitcnt & 0x00FF00FF00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF00FF00FF );
			bitcnt = (bitcnt & 0x0000FFFF0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF0000FFFF );

			bitcnt = (bitcnt & 0x00000000FFFFFFFF) + ( (bitcnt >> 32) & 0x00000000FFFFFFFF);
			bitcnt = (64 - bitcnt);

			if( bitcnt == 0 )
			{
				++bitcnt;
			};

			++cnt;
			pCheckSrc += bitcnt;

		};

	}else
	{
		return 0;
	};

	return cnt;
};

//第２引数に指定したタイプで強制的にカウントを行います。(SJIS混じりUTF8の対処)
uint64_t SonikLibStringConvert::GetStringCount(const char* pCheckSrc, SonikLibConvertType CountStrType)
{
	if( CountStrType != SCHTYPE_SJIS && CountStrType != SCHTYPE_UTF8)
	{
		return 0;
	};

//	SonikLibConvertType Type_ = SonikLibStringConvert::CheckConvertType(pCheckSrc);
	uint64_t cnt = 0;
	uint64_t bitcnt = 0;
	unsigned char swapbit = 0;

	if( CountStrType == SCHTYPE_SJIS )
	{
		while( (*pCheckSrc) != 0x00 )
		{
			if( (0x80 <= static_cast<unsigned char>((*pCheckSrc)) && static_cast<unsigned char>((*pCheckSrc)) <= 0x9F) ||  (0xE0 <= static_cast<unsigned char>((*pCheckSrc)) && static_cast<unsigned char>((*pCheckSrc)) <= 0xFC) )
			{

//				++cnt;
				++pCheckSrc;
			};

			++cnt;
			++pCheckSrc;
		};

	}else if( CountStrType == SCHTYPE_UTF8 )
	{
		while( (*pCheckSrc) != 0x00 )
		{
			swapbit = (*pCheckSrc);
			swapbit = SonikMathBit::BitSwapFor8bit(swapbit);

			bitcnt =  ~(swapbit);

			bitcnt |= (bitcnt << 1);
			bitcnt |= (bitcnt << 2);
			bitcnt |= (bitcnt << 4);
			bitcnt |= (bitcnt << 8);
			bitcnt |= (bitcnt << 16);
			bitcnt |= (bitcnt << 32);

//			bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
//			bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
//			bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
//			bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );

//			bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);

			bitcnt = (bitcnt & 0x5555555555555555) + ( (bitcnt >> 1) & 0x5555555555555555 );
			bitcnt = (bitcnt & 0x3333333333333333) + ( (bitcnt >> 2) & 0x3333333333333333 );
			bitcnt = (bitcnt & 0x0F0F0F0F0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F0F0F0F0F );
			bitcnt = (bitcnt & 0x00FF00FF00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF00FF00FF );
			bitcnt = (bitcnt & 0x0000FFFF0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF0000FFFF );

			bitcnt = (bitcnt & 0x00000000FFFFFFFF) + ( (bitcnt >> 32) & 0x00000000FFFFFFFF);

			bitcnt = (64 - bitcnt);
			if( bitcnt == 0 )
			{
				++bitcnt;
			};

			++cnt;
			pCheckSrc += bitcnt;

		};

	}else
	{
		return 0;
	};

	return cnt;
};


//unicode(UTF-16)文字の文字数を返却します。
uint64_t SonikLibStringConvert::GetStringCount(const char16_t* pCheckSrc)
{
	uint64_t cnt =0;

	while( (*pCheckSrc) != 0 )
	{
		++cnt;
		++pCheckSrc;
	};

	return cnt;

};

//unicode(UTF-32)文字の文字数を返却します。
uint64_t SonikLibStringConvert::GetStringCount(const int32_t* pCheckSrc)
{
	uint64_t cnt_ = 0;

	while( (*pCheckSrc) != 0 )
	{
		++cnt_;
		++pCheckSrc;
	};

	return cnt_;
};



//UTF-8をUNICODE(UTF-32)に変換します。
bool SonikLibStringConvert::ConvertUTF8ToUTF32(char* pSrc, int32_t* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 )
	{
		return false;
	};

	uint64_t SrcLen = GetStringCount(pSrc);


	if(pDest == 0 || pDest == nullptr)
	{
		if(DestBufferSize != 0 && DestBufferSize != nullptr)
		{
			(*DestBufferSize) = SrcLen + 1;
		}
		return false;
	};

	uint32_t* pUtf32_ = 0;

	pUtf32_ = new(std::nothrow) uint32_t[(SrcLen) + 1];
	if(pUtf32_ == 0 || pUtf32_ == nullptr)
	{
		return false;
	}
	std::fill_n(pUtf32_, (SrcLen+1), 0);


	uint64_t utf8_i = 0;
	uint64_t utf32_i = 0;
	unsigned char val = 0;
	uint64_t numBytes = 0;
	uint64_t offset_ = 0;

	for(offset_=0; offset_ < SrcLen;/*省略*/)
	{
		val = pSrc[utf8_i];
		numBytes = 0;

	    unsigned char* control_src = reinterpret_cast<unsigned char*>(pSrc);

		//utfのバイトセットチェック。
	    if (0 <= val && val < 0x80)
	    {
	    	numBytes = 1;

	    	pUtf32_[utf32_i] = (static_cast<uint32_t>(control_src[utf8_i]));

	    }else if (0xC2 <= val && val < 0xE0)
	    {
	    	numBytes = 2;

	    	if (!(0x80 <= control_src[utf8_i+1] && control_src[utf8_i+1] < 0xC0))
            {
            	delete[] pUtf32_;
                return false;
            };
            if ((control_src[utf8_i] & 0x1E) == 0)
            {
            	delete[] pUtf32_;
                return false;
            };

            pUtf32_[utf32_i] = (static_cast<uint32_t>(control_src[utf8_i] & 0x1F)) << 6;
            pUtf32_[utf32_i] |= static_cast<uint32_t>(control_src[utf8_i] & 0x3F);

	    }else if (0xE0 <= val && val < 0xF0)
	    {
	    	numBytes = 3;

            if ((!(0x80 <= control_src[utf8_i+1] && control_src[utf8_i+1] < 0xC0)) ||
            	(!(0x80 <= control_src[utf8_i+2] && control_src[utf8_i+2] < 0xC0))
				)
            {
            	delete[] pUtf32_;
                return false;
            };
            if ((control_src[utf8_i] & 0x0F) == 0 &&
                (control_src[utf8_i+1] & 0x20) == 0)
            {
            	delete[] pUtf32_;
                return false;
            };

            pUtf32_[utf32_i] = static_cast<uint32_t>(control_src[utf8_i] & 0x0F) << 12;
            pUtf32_[utf32_i] |= static_cast<uint32_t>(control_src[utf8_i+1] & 0x3F) << 6;
            pUtf32_[utf32_i] |= static_cast<uint32_t>(control_src[utf8_i+2] & 0x3F);

	    }else if (0xF0 <= val && val < 0xF8)
	    {
	    	numBytes = 4;

            if ((!(0x80 <= control_src[utf8_i+1] && control_src[utf8_i+1] < 0xC0)) ||
            	(!(0x80 <= control_src[utf8_i+2] && control_src[utf8_i+2] < 0xC0)) ||
				(!(0x80 <= control_src[utf8_i+3] && control_src[utf8_i+3] < 0xC0)))
            {
            	delete[] pUtf32_;
                return false;
            };
            if ((control_src[utf8_i] & 0x07) == 0 &&
                (control_src[utf8_i+1] & 0x30) == 0)
            {
            	delete[] pUtf32_;
                return false;
            };

            pUtf32_[utf32_i] = static_cast<uint32_t>(control_src[utf8_i] & 0x07) << 18;
            pUtf32_[utf32_i] |= static_cast<uint32_t>(control_src[utf8_i+1] & 0x3F) << 12;
            pUtf32_[utf32_i] |= static_cast<uint32_t>(control_src[utf8_i+2] & 0x3F) << 6;
            pUtf32_[utf32_i] |= static_cast<uint32_t>(control_src[utf8_i+3] & 0x3F);

	    };

	    if( numBytes == 0)
	    {
	    	delete[] pUtf32_;
	    	return false;
	    };

	    utf8_i += numBytes;
	    ++offset_;
	    ++utf32_i;
	};

	pUtf32_[utf32_i] = 0;
	++utf32_i;

	errno_t a = memcpy_s(pDest, sizeof(uint32_t) * (*DestBufferSize), pUtf32_, (4*utf32_i));
	if(  a != 0 )
	{
		delete[] pUtf32_;
		return false;
	};

	delete[] pUtf32_;
    return true;
};

//UNICODE(UTF-32)をUTF-8に変換します。
bool SonikLibStringConvert::ConvertUTF32ToUTF8(int32_t* pSrc, char* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 )
	{
		return false;
	};

	uint64_t strcnt_ = 0;
	uint32_t* tmpsrc = reinterpret_cast<uint32_t*>(pSrc);
	while( (*tmpsrc) != 0 )
	{
		++tmpsrc;
		++strcnt_;
	};

	if(pDest == 0 || pDest == nullptr)
	{
		if(DestBufferSize != 0 && DestBufferSize != nullptr)
		{
			(*DestBufferSize) = (strcnt_ << 2) + 1; // x * 4 = x << 2;
		};
		return false;
	}

	uint8_t* utf8buffer = new(std::nothrow) uint8_t[(strcnt_ << 2) +1]; // x * 4 = x << 2
	if(utf8buffer == 0 || utf8buffer == nullptr)
	{
		return false;
	};
	std::fill_n(utf8buffer, ((strcnt_ << 2) +1), 0); // x * 4 = x << 2

	//unsigned long utf8offset = 0;
	unsigned char* p_utf8offset = reinterpret_cast<unsigned char*>(utf8buffer);

	tmpsrc = reinterpret_cast<uint32_t*>(pSrc);
	for(uint32_t i=0; i < strcnt_; ++i)
	{
		if( (*tmpsrc) < 0 || (*tmpsrc) > 0x10FFFF)
		{
			delete[] utf8buffer;
			return false;
		};

		if( (*tmpsrc) < 128 )
		{
//			utf8buffer[utf8offset] = static_cast<char>((*pSrc));
			(*p_utf8offset) = static_cast<unsigned char>((*tmpsrc));
			++p_utf8offset;
//			utf8buffer[utf8offset+1] = 0;
//			utf8buffer[utf8offset+2] = 0;
//			utf8buffer[utf8offset+3] = 0;

		}else if( (*tmpsrc) < 2048 )
		{
//			utf8buffer[utf8offset] = 0xC0 | static_cast<char>( ((*pSrc) >> 6) );
			(*p_utf8offset) = 0xC0 | static_cast<unsigned char>( ((*tmpsrc) >> 6) );
			++p_utf8offset;
//			utf8buffer[utf8offset+1] = 0x80 | static_cast<char>( ((*pSrc) & 0x3F) );
			(*p_utf8offset) = 0x80 | static_cast<unsigned char>( ((*tmpsrc) & 0x3F) );
			++p_utf8offset;
//			utf8buffer[utf8offset+2] = 0;
//			utf8buffer[utf8offset+3] = 0;

		}else if( (*tmpsrc) < 65536 )
		{
//			utf8buffer[utf8offset] = 0xE0 | static_cast<char>( ((*pSrc) >>12) );
//			utf8buffer[utf8offset+1] = 0x80 | static_cast<char>( (((*pSrc) >> 6) & 0x3F) );
//			utf8buffer[utf8offset+2] = 0x80 | static_cast<char>( ((*pSrc) & 0x3F) );
//			utf8buffer[utf8offset+3] = 0;
			(*p_utf8offset) = 0xE0 | static_cast<unsigned char>( ((*tmpsrc) >>12) );
			++p_utf8offset;
			(*p_utf8offset) = 0x80 | static_cast<unsigned char>( (((*tmpsrc) >> 6) & 0x3F) );
			++p_utf8offset;
			(*p_utf8offset) = 0x80 | static_cast<unsigned char>( ((*tmpsrc) & 0x3F) );
			++p_utf8offset;

		}else
		{
//			utf8buffer[utf8offset] = static_cast<char>( ((*pSrc) >> 18) );
//			utf8buffer[utf8offset+1] = static_cast<char>( ((*pSrc) >> 12) & 0x3F );
//			utf8buffer[utf8offset+2] = static_cast<char>( ((*pSrc) >> 6) & 0x3F );
//			utf8buffer[utf8offset+3] = static_cast<char>( ((*pSrc) & 0x3F) );
			(*p_utf8offset) = static_cast<unsigned char>( ((*tmpsrc) >> 18) );
			++p_utf8offset;
			(*p_utf8offset) = static_cast<unsigned char>( ((*tmpsrc) >> 12) & 0x3F );
			++p_utf8offset;
			(*p_utf8offset) = static_cast<unsigned char>( ((*tmpsrc) >> 6) & 0x3F );
			++p_utf8offset;
			(*p_utf8offset) = static_cast<unsigned char>( ((*tmpsrc) & 0x3F) );
			++p_utf8offset;

		};

		++tmpsrc;
//		utf8offset += 4;
	};

	errno_t a = memcpy_s(pDest, (*DestBufferSize), utf8buffer, (strcnt_*4+1));
	if(  a != 0 )
	{
		delete[] utf8buffer;
		return false;
	};

	delete[] utf8buffer;
	return true;
};

//UNICODE(UTF-32)をUNICODE(UTF-16)に変換します。
bool SonikLibStringConvert::ConvertUTF32ToUTF16(int32_t* pSrc, char16_t* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 )
	{
		return false;
	};

	uint64_t srclen_ = SonikLibStringConvert::GetStringCount(pSrc);
	uint64_t wsrclen_ = (srclen_ << 1) + 1;  // x * 2 = x << 1 * NULL終端

	if(pDest == 0 || pDest == nullptr)
	{
		if(DestBufferSize != 0 && DestBufferSize != nullptr)
		{
			//NULL終端追加
			(*DestBufferSize) = wsrclen_;
		};
		return false;
	}

	uint16_t* utf16buffer = new(std::nothrow) uint16_t[ wsrclen_ ];
	if(utf16buffer == 0 || utf16buffer == nullptr)
	{
		return false;
	};

	std::fill_n(utf16buffer, wsrclen_, 0 );

	uint32_t* utf32_Src = reinterpret_cast<uint32_t*>(pSrc);
	uint16_t* pSrc_shortbyte = nullptr;
	uint16_t* p_cont_utf16buffer = utf16buffer;
	for(uint64_t i=0; i < srclen_; ++i)
	{
		if(utf32_Src[i] < 0 || utf32_Src[i] > 0x10FFFF)
		{
			delete[] utf16buffer;
			return false;
		};

		if(utf32_Src[i] < 0x10000)
		{
//			utf16buffer[utf16offset] = static_cast<wchar_t>(pSrc[i]);
//			utf16buffer[utf16offset] = 0;
			pSrc_shortbyte = reinterpret_cast<uint16_t*>(&utf32_Src[i]);
			(*p_cont_utf16buffer) = (*pSrc_shortbyte);
			++p_cont_utf16buffer;
			++pSrc_shortbyte;
//			(*p_cont_utf16buffer) = (*pSrc_shortbyte);
//			++p_cont_utf16buffer;

		}else
		{
//			utf16buffer[utf16offset] = static_cast<wchar_t>( ((pSrc[i] - 0x10000) >> 10) + 0xD800 ); // x / 0x400 = x / 1024 = x >> 10
//			utf16buffer[utf16offset] = static_cast<wchar_t>( ((pSrc[i] - 0x10000) & 0x3FF) + 0xD800 ); // x % 0x400 = x % 1024 = x & 1023 = x & (0x400 - 1) = x & 0x3FF

			(*p_cont_utf16buffer) = static_cast<uint16_t>( ((utf32_Src[i] - 0x10000) >> 10) + 0xD800 ); // x / 0x400 = x / 1024 = x >> 10
			++p_cont_utf16buffer;
			(*p_cont_utf16buffer) = static_cast<uint16_t>( ((utf32_Src[i] - 0x10000) & 0x3FF) + 0xD800 ); // x % 0x400 = x % 1024 = x & 1023 = x & (0x400 - 1) = x & 0x3FF
			++p_cont_utf16buffer;
		};

	};

	errno_t a = memcpy_s(pDest, (*DestBufferSize) << 1, utf16buffer, (wsrclen_ << 1));
	if(  a != 0 )
	{
		delete[] utf16buffer;
		return false;
	};

	return true;
};

//UNICODE(UTF-16)をUNICODE(UTF-32)に変換します。
bool SonikLibStringConvert::ConvertUTF16ToUTF32(char16_t* pSrc, int32_t* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 )
	{
		return false;
	};

	uint64_t srclen_ = SonikLibStringConvert::GetStringCount(pSrc);

	if( pDest == 0 || pDest ==nullptr )
	{
		if(DestBufferSize != 0 && DestBufferSize != nullptr)
		{
			(*DestBufferSize) = srclen_ + 1;
		}
		return false;
	}


	uint32_t* utf32buffer = new(std::nothrow) uint32_t[ srclen_ + 1 ]; //NULL文字分追加
	if(utf32buffer == 0 || utf32buffer == nullptr)
	{
		return false;
	};

	std::fill_n(utf32buffer, (srclen_ + 1), 0 );


	//配列組み換え
	uint16_t* utf16buffer = reinterpret_cast<uint16_t*>(pSrc);

	for(uint64_t i=0; i < srclen_; ++i)
	{
		if( 0xD800 <= utf16buffer[0] && utf16buffer[0] < 0xDC00  )
		{
//			if( 0xDC00 <= utf16buffer[1] && utf16buffer[1] < 0xDC00 )
			if( 0xDC00 <= utf16buffer[1])
			{
				utf32buffer[i] = 0x10000 + ( utf16buffer[0] - 0xD800 ) * 0x400 + ( utf16buffer[1] - 0xDC00 );

				utf16buffer += 2;

			}else if( utf16buffer[1] == 0 )
			{
				utf32buffer[i] = utf16buffer[0];

				utf16buffer += 1;

			}else
			{
				delete[] utf32buffer;
				return false;
			};

		}else if( 0xDC00 <= (*utf16buffer) && (*utf16buffer) < 0xE000 )
		{
			if( utf16buffer[1] == 0 )
			{
				utf32buffer[i] = utf16buffer[0];

				utf16buffer += 1;

			}else
			{
				delete[] utf32buffer;
				return false;
			};

		}else
		{
			utf32buffer[i] = utf16buffer[0];

			utf16buffer += 1;

		};


	};


	errno_t a = memcpy_s(pDest, (((*DestBufferSize)-1) << 2) + 4, utf32buffer, (srclen_ << 2) + 4);
	if(  a != 0 )
	{
		delete[] utf32buffer;
		return false;
	};

	delete[] utf32buffer;
	return true;
};


//UNICODE(UTF-16)をUTF8に変換します。
bool SonikLibStringConvert::ConvertUTF16ToUTF8(char16_t* pSrc, char* pDest, uint64_t* DestBufferSize)
{
	uint64_t buffersize = 0;
	SonikLibStringConvert::ConvertUTF16ToUTF32(pSrc, nullptr, &buffersize);

	int32_t* utf32buffer = new(std::nothrow) int32_t[buffersize];
	if(utf32buffer == 0 || utf32buffer == nullptr)
	{
		return false;
	};

	if( !SonikLibStringConvert::ConvertUTF16ToUTF32(pSrc, utf32buffer, &buffersize) )
	{
		delete[] utf32buffer;
		return false;
	};

	SonikLibStringConvert::ConvertUTF32ToUTF8(utf32buffer, nullptr, &buffersize);

	if(pDest == 0 || pDest == nullptr)
	{
		if(DestBufferSize != 0 && DestBufferSize != nullptr)
		{
			(*DestBufferSize) = buffersize;
		};
		delete[] utf32buffer;
		return false;
	};

	char* utf8buffer = new(std::nothrow) char[buffersize];
	if(utf8buffer == 0 || utf8buffer == nullptr)
	{
		delete[] utf32buffer;
		return false;
	};

	if( !SonikLibStringConvert::ConvertUTF32ToUTF8(utf32buffer, utf8buffer, &buffersize) )
	{
		delete[] utf32buffer;
		delete[] utf8buffer;
		return false;
	};

	errno_t a = memcpy_s(pDest, (*DestBufferSize), utf8buffer, buffersize);
	if(  a != 0 )
	{
		delete[] utf8buffer;
		delete[] utf32buffer;
		return false;
	};

	delete[] utf32buffer;
	delete[] utf8buffer;
	return true;
};

//bool SonikLibStringConvert::ConvertUTF16ToUTF8(wchar_t* pSrc, char* pDest, unsigned long* DestBufferSize)
//{
//	if( pSrc == 0 )
//	{
//		return false;
//	};
//
//	unsigned long SrcLen = wcslen(pSrc);
//	char* pUtf16_ = reinterpret_cast<char*>(pSrc);
//	char* pUtf8_ = 0;
//
//	try
//	{
//		pUtf8_ = new char[SrcLen * 3 + 1];
//	}catch(std::bad_alloc& e)
//	{
//		return false;
//	};
//
//	std::fill_n(pUtf8_, (SrcLen*3+1), 0);
//
//	unsigned long looped = 0;
//	unsigned long looped_utf8 = 0;
//	if( pSrc[0] == 0xFFFE || pSrc[0] == 0xFEFF )
//	{
//		++looped;
//	};
//
//	wchar_t wcsval;
//	for(/*省略*/; looped < SrcLen; ++looped)
//	{
//		wcsval = pSrc[looped];
//		pUtf16_ = reinterpret_cast<char*>(&wcsval);
//
//		if(0x0001 <= wcsval && wcsval <= 0x007F)
//		{
//			//１バイトのUTF8変換
//			pUtf8_[looped_utf8] = pUtf16_[0];
//			++looped_utf8;
//
//		}else if(0x0080 <= wcsval && wcsval <= 0x07FF)
//		{
//			//2バイトのUTF8変換
//			pUtf8_[looped_utf8] = (0xC0 | (((pUtf16_[1] & 0x07) << 2) | ((pUtf16_[0] & 0xC0) >> 6)));
//			++looped_utf8;
//			pUtf8_[looped_utf8] = (0x80 | (pUtf16_[0] & 0x3F));
//			++looped_utf8;
//
//		}else if(0x0800 <= wcsval && wcsval <= 0xFFFF)
//		{
//			//3バイトのUTF8変換
//			pUtf8_[looped_utf8] = (0xE0 | ((pUtf16_[1] & 0xF0) >> 4));
//			++looped_utf8;
//			pUtf8_[looped_utf8] = (0x80 | (((pUtf16_[1] & 0x0F) << 2) | ((pUtf16_[0] & 0xC0) >> 6)));
//			++looped_utf8;
//			pUtf8_[looped_utf8] = (0x80 | (pUtf16_[0] & 0x3F));
//			++looped_utf8;
//
//		};
//
//	};
//
//	if(pDest == 0)
//	{
//		delete[] pUtf8_;
//		if(DestBufferSize != 0)
//		{
//			(*DestBufferSize) = looped_utf8;
//		};
//
//		return false;
//	};
//
//	if( (*DestBufferSize) != 0 )
//	{
//		if(looped_utf8 > (*DestBufferSize) )
//		{
//			delete[] pUtf8_;
//			return false;
//		};
//	};
//
//	errno_t a = memcpy_s(pDest, (*DestBufferSize), pUtf8_, looped_utf8);
//	if(  a != 0 )
//	{
//		delete[] pUtf8_;
//		return false;
//	}
//
//	(*DestBufferSize) = looped_utf8;
//
//	delete[] pUtf8_;
//	return true;
//};

//UTF8をUNICODE(UTF-16)に変換します。
bool SonikLibStringConvert::ConvertUTF8ToUTF16(char* pSrc, char16_t* pDest, uint64_t* DestBufferSize)
{
	uint64_t buffersize = 0;
	SonikLibStringConvert::ConvertUTF8ToUTF32(pSrc, nullptr, &buffersize);

	int32_t* utf32buffer = new(std::nothrow) int32_t[buffersize];
	if(utf32buffer == 0 || utf32buffer == nullptr)
	{
		return false;
	};

	if( !SonikLibStringConvert::ConvertUTF8ToUTF32(pSrc, utf32buffer, &buffersize) )
	{
		delete[] utf32buffer;
		return false;
	};

	SonikLibStringConvert::ConvertUTF32ToUTF16(utf32buffer, nullptr, &buffersize);

	if(pDest == 0 || pDest == nullptr)
	{
		if(DestBufferSize != 0 && DestBufferSize != nullptr)
		{
			(*DestBufferSize) = buffersize;
		};
		delete[] utf32buffer;
		return false;
	}

	char16_t* utf16buffer = new(std::nothrow) char16_t[buffersize];
	if(utf16buffer == 0 || utf16buffer == nullptr)
	{
		delete[] utf32buffer;
		return false;
	};

	if( !SonikLibStringConvert::ConvertUTF32ToUTF16(utf32buffer, utf16buffer, &buffersize) )
	{
		return false;
	};

	errno_t a = memcpy_s(pDest, (*DestBufferSize) << 1, utf16buffer, buffersize << 1);
	if(  a != 0 )
	{
		delete[] utf16buffer;
		delete[] utf32buffer;
		return false;
	}

	delete[] utf16buffer;
	delete[] utf32buffer;
	return true;
};

//bool SonikLibStringConvert::ConvertUTF8ToUTF16(char* pSrc, wchar_t* pDest, unsigned long* DestBufferSize)
//{
//	if(pSrc == 0)
//	{
//		return false;
//	};
//
//	unsigned long SrcLen = strlen(pSrc);
//	if((SrcLen & 0x01) == 1)
//	{
//		++SrcLen;
//	};
//	SrcLen >>= 1;
//
//	wchar_t* pUtf16_ = 0;
//	try
//	{
//		pUtf16_ = new wchar_t[SrcLen];
//	}catch(std::bad_alloc& e)
//	{
//		return false;
//	};
//
//	std::fill_n(pUtf16_, SrcLen, 0);
//
//	unsigned long looped = 0;
//	unsigned long wcslooped = 0;
//
//	SrcLen <<= 1;
//	for(/*省略*/; looped < SrcLen;/*省略*/)
//	{
//		char* utf8val = &pSrc[looped];
//		char* wcsval = reinterpret_cast<char*>(&pUtf16_[wcslooped]);
//
//		if( ((*utf8val) & 0x80) == 0 )
//		{
//			//UTF8 の1バイト文字と判定
//			wcsval[0] = (*utf8val);
//
//			++looped;
//			++wcslooped;
//
//		}else if( ((*utf8val) & 0x20) == 0 )
//		{
//			//utf8の2バイト文字と判定
//			wcsval[1] = (((*utf8val) & 0x1C) >> 2);
//			wcsval[0] = ((((*utf8val) & 0x03) << 6) | ((*(utf8val+1)) & 0x3F));
//			looped += 2;
//			++wcslooped;
//
//		}else if( ((*utf8val) & 0x10) == 0 )
//		{
//			//utf8の3バイト文字と判定
//			wcsval[1] = ((((*utf8val) & 0x0F) << 4) | (((*(utf8val+1)) & 0x3C) >> 2));
//			wcsval[0] = ((((*(utf8val+1)) & 0x03) << 6) | ((*(utf8val+2)) & 0x3F));
//			looped += 3;
//			++wcslooped;
//		};
//	};
//
//	if(pDest == 0)
//	{
//		delete[] pUtf16_;
//
//		if(DestBufferSize != 0)
//		{
//			(*DestBufferSize) = wcslooped +1;
//		};
//
//		return false;
//	};
//
//	if( (*DestBufferSize) != 0 )
//	{
//		if(wcslooped > (*DestBufferSize) )
//		{
//			delete[] pUtf16_;
//			return false;
//		};
//	};
//
//	if( memcpy_s(pDest, ((*DestBufferSize) << 1), pUtf16_, ((wcslooped +1) << 1)) != 0 )
//	{
//		delete[] pUtf16_;
//		return false;
//	};
//
//	(*DestBufferSize) = wcslooped +1;
//
//	delete pUtf16_;
//	return true;
//};



//マルチバイト文字列をUTF8文字列に変換します。
//第１引数の文字列は、可能性の判定として、SJIS判定であれば処理を行います。
bool SonikLibStringConvert::ConvertMBSToUTF8(char* pSrc, char* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 )
	{
		return false;
	};

	if( SonikLibStringConvert::CheckConvertType(pSrc) != SCHTYPE_SJIS )
	{
		return false;
	};

	uint64_t SrcLen = SonikLibStringConvert::GetStringCount(pSrc);
	uint64_t utf16Len = SrcLen;

	char16_t* unicode_buf = 0;

	try
	{
		unicode_buf = new char16_t[utf16Len + 1];

	}catch(std::bad_alloc& e)
	{
		return false;
	};

	std::fill_n(unicode_buf, (utf16Len + 1), 0);


	setlocale(LC_CTYPE, "jpn");

	//sjis -> utf16
	uint64_t retsize = 0;
	errno_t err = 0;
	err = mbstowcs_s(&retsize, NULL, 0, pSrc, 0);
	err = mbstowcs_s(&retsize, reinterpret_cast<wchar_t*>(unicode_buf), utf16Len+1, pSrc, SrcLen);
	if( err != 0 )
	{
		delete[] unicode_buf;
		return false;
	};

	setlocale(LC_CTYPE, "");

	uint64_t sizecheck = 0;
	if(pDest == 0)
	{
		if( DestBufferSize != 0 )
		{
			//utf16->utf8 サイズチェック
			SonikLibStringConvert::ConvertUTF16ToUTF8(unicode_buf, 0, &sizecheck);
			(*DestBufferSize) = sizecheck;
		};
		delete[] unicode_buf;
		return false;
	};

	//utf16->utf8 本番
	if( !SonikLibStringConvert::ConvertUTF16ToUTF8(unicode_buf, pDest, DestBufferSize) )
	{
		delete[] unicode_buf;
		return false;
	};

	delete[] unicode_buf;
	return true;
};

//UTF8文字列をマルチバイト文字列に変換します。
//第１引数の文字列は、可能性の判定として、SJIS判定であれば処理を行います。
//第１引数の文字列に対して、Null終端がない場合の動作は、strlenと同様にバッファオーバーランを起こします。
bool SonikLibStringConvert::ConvertUTF8ToMBS(char* pSrc, char* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 )
	{
		return false;
	};

	if( SonikLibStringConvert::CheckConvertType(pSrc) != SCHTYPE_UTF8 )
	{
		return false;
	};

//	unsigned int SrcLen = strlen(pSrc);
	uint64_t utf16Len = 0;

	SonikLibStringConvert::ConvertUTF8ToUTF16(pSrc, 0, &utf16Len);
//	++utf16Len;

	char16_t* unicode_buf = 0;
	try
	{
		unicode_buf = new char16_t[utf16Len + 1];

	}catch(std::bad_alloc& e)
	{
		return false;
	};

	std::fill_n(unicode_buf, utf16Len + 1, 0);

	//UTF8 -> UTF16
	if( !SonikLibStringConvert::ConvertUTF8ToUTF16(pSrc, unicode_buf, &utf16Len) )
	{
		return false;
	};

	uint64_t retsize = 0;
	if(pDest == 0)
	{
		if( DestBufferSize != 0 )
		{
			//utf16->SJIS サイズチェック
			setlocale(LC_CTYPE, "jpn");
			wcstombs_s(&retsize, 0, 0, reinterpret_cast<wchar_t*>(unicode_buf), utf16Len);
			setlocale(LC_CTYPE, "");
			(*DestBufferSize) = retsize;
		};
		delete[] unicode_buf;
		return false;
	};

	if( DestBufferSize == 0 )
	{
		delete[] unicode_buf;
		return false;
	};

	//utf16->SJIS 本番
	setlocale(LC_CTYPE, "jpn");
	if( wcstombs_s(&retsize, pDest, (*DestBufferSize), reinterpret_cast<wchar_t*>(unicode_buf), (utf16Len +1)) != 0 )
	{
		delete[] unicode_buf;
		setlocale(LC_CTYPE, "");
		return false;
	};

	setlocale(LC_CTYPE, "");
	return true;
};

//マルチバイト文字列をUTF16文字列に変換します。
//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
bool SonikLibStringConvert::ConvertMBStoUTF16(char* pSrc, char16_t* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 || SonikLibStringConvert::CheckConvertType(pSrc) != SCHTYPE_SJIS)
	{
		return false;
	};

	setlocale(LC_CTYPE, "jpn");

	uint64_t size_ = 0;
	uint64_t SrcLen = SonikLibStringConvert::GetStringLengthByte(pSrc);
	mbstowcs_s(&size_, 0, 0, pSrc, SrcLen);

	char16_t* tmpBuf = 0;
	try
	{
		tmpBuf = new char16_t[size_ + 1]; // NULL終端追加
	}catch(std::bad_alloc&)
	{
		return false;
	};

	std::fill_n(tmpBuf, size_ + 1, 0);

	if( pDest == 0 )
	{
		if( DestBufferSize != 0 )
		{
			(*DestBufferSize) = size_;
			setlocale(LC_CTYPE, "");
			delete[] tmpBuf;
			return false;
		};
	};

	if( DestBufferSize == 0 )
	{
		setlocale(LC_CTYPE, "");
		delete[] tmpBuf;
		return false;
	};

	if( mbstowcs_s(0, reinterpret_cast<wchar_t*>(tmpBuf), size_, pSrc, SrcLen) != 0 )
	{
		setlocale(LC_CTYPE, "");
		delete[] tmpBuf;
		return false;
	};

	setlocale(LC_CTYPE, "");

	if( memcpy_s(pDest, ((*DestBufferSize) << 1), tmpBuf, size_) != 0 ) // x * 2 = x << 1
	{
		delete[] tmpBuf;
		return false;
	};

	delete[] tmpBuf;
	return true;
};

//UTF16文字列をマルチバイト文字列に変換します。
//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
bool SonikLibStringConvert::ConvertUTF16toMBS(char16_t* pSrc, char* pDest, uint64_t* DestBufferSize)
{
	if( pSrc == 0 )
	{
		return false;
	};

	setlocale(LC_CTYPE, "jpn");

	uint64_t size_ = 0;
	uint64_t SrcLen = SonikLibStringConvert::GetStringLengthByte(pSrc);
	wcstombs_s(&size_, 0, 0, reinterpret_cast<wchar_t*>(pSrc), SrcLen);

	char* tmpBuf = 0;
	try
	{
		tmpBuf = new char[size_ + 1];
	}catch(std::bad_alloc&)
	{
		return false;
	};

	std::fill_n(tmpBuf, size_ + 1, 0);

	if( pDest == 0 )
	{
		if( DestBufferSize != 0 )
		{
			(*DestBufferSize) = size_ + 1;
			setlocale(LC_CTYPE, "");
			delete[] tmpBuf;
			return false;
		};
	};

	if( DestBufferSize == 0 )
	{
		setlocale(LC_CTYPE, "");
		delete[] tmpBuf;
		return false;
	};

	if( wcstombs_s(0, tmpBuf, size_, reinterpret_cast<wchar_t*>(pSrc), SrcLen) != 0 )
	{
		setlocale(LC_CTYPE, "");
		delete[] tmpBuf;
		return false;
	};

	setlocale(LC_CTYPE, "");

	if( memcpy_s(pDest, (*DestBufferSize), tmpBuf, size_) != 0 )
	{
		delete[] tmpBuf;
		return false;
	};

	delete[] tmpBuf;
	return true;
};


bool SonikLibStringConvert::ConvertUTF8FWCToHWCForAN(const char* ConvertStr, char* dst, uint64_t& UsedSize)
{
	SonikLibConvertType type_ = 	CheckConvertType(ConvertStr);
	if( SonikLibConvertType::SCHTYPE_UTF8 != type_ )
	{
		//UTF8じゃない模様。
		return false;
	};

	uint64_t StrByte = SonikLibStringConvert::GetStringLengthByte(ConvertStr);
	if( (StrByte & 0x01) != 0 )
	{
		++StrByte;
	};
	char16_t* buffer = new(std::nothrow) char16_t[ (StrByte >> 1) ];
	if( buffer == nullptr || buffer == 0 )
	{
		//c:確保失敗
		return false;
	};


	uint64_t cnt = 0;
	uint64_t bitcnt = 0;
	uint64_t PlusValue = 0;
	uint64_t Offset = 0;
	unsigned char swapbit = 0;
	char* InsertPoint = reinterpret_cast<char*>(buffer);

	while( static_cast<unsigned char>((*ConvertStr)) != 0x00 )
	{
		swapbit = (*ConvertStr);
		swapbit = SonikMathBit::BitSwapFor8bit(swapbit);

		bitcnt =  ~(swapbit);

		bitcnt |= (bitcnt << 1);
		bitcnt |= (bitcnt << 2);
		bitcnt |= (bitcnt << 4);
		bitcnt |= (bitcnt << 8);
		bitcnt |= (bitcnt << 16);
		bitcnt |= (bitcnt << 32);

//		bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
//		bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
//		bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
//		bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );
//
//		bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
//		bitcnt = (32 - bitcnt);

		bitcnt = (bitcnt & 0x5555555555555555) + ( (bitcnt >> 1) & 0x5555555555555555 );
		bitcnt = (bitcnt & 0x3333333333333333) + ( (bitcnt >> 2) & 0x3333333333333333 );
		bitcnt = (bitcnt & 0x0F0F0F0F0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F0F0F0F0F );
		bitcnt = (bitcnt & 0x00FF00FF00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF00FF00FF );
		bitcnt = (bitcnt & 0x0000FFFF0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF0000FFFF );

		bitcnt = (bitcnt & 0x00000000FFFFFFFF) + ( (bitcnt >> 32) & 0x00000000FFFFFFFF);

		bitcnt = (64 - bitcnt);
		if( bitcnt == 0 )
		{
			++bitcnt;
		};

		PlusValue = 0;
		Offset = 0;
		if( bitcnt == 3 )
		{
			PlusValue |= static_cast<unsigned char>(ConvertStr[0]);
			PlusValue = ( (PlusValue << 8) | static_cast<unsigned char>(ConvertStr[1]) );
			PlusValue = ( (PlusValue << 8) | static_cast<unsigned char>(ConvertStr[2]) );

			if( 0xEFBC81 <= PlusValue && PlusValue <= 0xEFBD9E )
			{
				//c:範囲内なら処理
				PlusValue -= 0xEFBC60;
				//BCとBD間は0x40(64)ずらすとぴったしになる。
				Offset = (static_cast<unsigned char>(ConvertStr[1]) - 0xBC) * 64;
				PlusValue += Offset;

				(*InsertPoint) = static_cast<char>(PlusValue);
				++InsertPoint;
				++cnt;

				ConvertStr += bitcnt;


				continue;
			};

		};

		memmove(InsertPoint, ConvertStr, bitcnt);

		InsertPoint += bitcnt;
		ConvertStr += bitcnt;
		cnt += bitcnt;


	};//end while

	(*InsertPoint) = 0x00;
	++cnt;

	if( dst == nullptr )
	{
		UsedSize = cnt;
		delete[] buffer;
		return true;
	};

	if( UsedSize < cnt )
	{
		//c:領域不足
		delete[] buffer;
		return false;
	};

	memcpy(dst, buffer, cnt);
	UsedSize = cnt;
	delete[] buffer;
	return true;
};

//UTF8文字列のおける、全角カナを半角カナに変換します。
bool SonikLibStringConvert::ConvertUTF8FWCToHWCForKANA(const char* ConvertStr, char* dst, uint64_t& UsedSize)
{
	SonikLibConvertType type_ = 	CheckConvertType(ConvertStr);
	if( SonikLibConvertType::SCHTYPE_UTF8 != type_ )
	{
		//UTF8じゃない模様。
		return false;
	};

	//c:最大現在のサイズ * 2のサイズになるので確保する。
	uint64_t StrSize = SonikLibStringConvert::GetStringLengthByte(ConvertStr);
	//NULL文字分プラス
	++StrSize;

	//1Byteカウントで2Byte配列なのでそのまま指定で２倍サイズ。
	char16_t* buffer = new(std::nothrow) char16_t[ StrSize ];
	memset(buffer, 0, (StrSize << 1) );

	uint64_t cnt = 0;
	uint64_t bitcnt = 0;
	uint64_t PlusValue = 0;
//	unsigned long PlusValue_sec = 0;
	uint64_t Offset_first = 0;
	uint64_t Offset_second = 0;
	unsigned char swapbit = 0;
	char* InsertPoint = reinterpret_cast<char*>(buffer);
	char* InsertTopPoint = InsertPoint;
	unsigned char* PlusValueAccess = nullptr;

	while( static_cast<unsigned char>((*ConvertStr)) != 0x00 )
	{
		swapbit = (*ConvertStr);
		swapbit = SonikMathBit::BitSwapFor8bit(swapbit);

		bitcnt =  ~(swapbit);

		bitcnt |= (bitcnt << 1);
		bitcnt |= (bitcnt << 2);
		bitcnt |= (bitcnt << 4);
		bitcnt |= (bitcnt << 8);
		bitcnt |= (bitcnt << 16);
		bitcnt |= (bitcnt << 32);

//		bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
//		bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
//		bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
//		bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );
//
//		bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
//		bitcnt = (32 - bitcnt);

		bitcnt = (bitcnt & 0x5555555555555555) + ( (bitcnt >> 1) & 0x5555555555555555 );
		bitcnt = (bitcnt & 0x3333333333333333) + ( (bitcnt >> 2) & 0x3333333333333333 );
		bitcnt = (bitcnt & 0x0F0F0F0F0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F0F0F0F0F );
		bitcnt = (bitcnt & 0x00FF00FF00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF00FF00FF );
		bitcnt = (bitcnt & 0x0000FFFF0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF0000FFFF );

		bitcnt = (bitcnt & 0x00000000FFFFFFFF) + ( (bitcnt >> 32) & 0x00000000FFFFFFFF);

		bitcnt = (64 - bitcnt);

		if( bitcnt == 0 )
		{
			++bitcnt;
		};

		PlusValue = 0;
//		PlusValue_sec = 0;
		Offset_first = 0;
		Offset_second = 0;
		if( bitcnt == 3 )
		{
			PlusValue |= static_cast<unsigned char>(ConvertStr[0]);
			PlusValue = ( (PlusValue << 8) | static_cast<unsigned char>(ConvertStr[1]) );
			PlusValue = ( (PlusValue << 8) | static_cast<unsigned char>(ConvertStr[2]) );

			if( 0xE382A1 <= PlusValue && PlusValue <= 0xE383BA )
			{
				//c:範囲内なら処理
				Offset_first = static_cast<unsigned char>(ConvertStr[1]) - 0x82;
				Offset_second = PlusValue - SonikConvStaticTable::HW_KANA_OFFSET_STARTPOINT[ (static_cast<unsigned char>(ConvertStr[1]) - 0x82) ] + (Offset_first * 33);


				//c:配列から値検索
				PlusValue = SonikConvStaticTable::HW_KANA[Offset_second];
				PlusValueAccess = reinterpret_cast<unsigned char*>(&PlusValue);
				Offset_first = ( ( ( PlusValueAccess[0] & 0x80 ) >> 7 ) * 3) + 3;	//InsertPointをずらす値を取得
				Offset_second = ( PlusValueAccess[0] & 0x7F );		//c: 濁点位置の取得

				//c:変更前のポイントの取得
				InsertTopPoint = InsertPoint;
				//c:代入処理
				(*InsertPoint) = static_cast<char>(PlusValueAccess[3]);
				++InsertPoint;
				(*InsertPoint) = static_cast<char>(PlusValueAccess[2]);
				++InsertPoint;
				(*InsertPoint) = static_cast<char>(PlusValueAccess[1]);
				++InsertPoint;

				//c:濁点位置に代入。0ならｧが入るが、ポインタは３つしか動かないため、次回代入時に消えるか１Byte目に終点文字である0が入る
				PlusValue = SonikConvStaticTable::HW_KANA[Offset_second];
				(*InsertPoint) = static_cast<char>(PlusValueAccess[3]);
				++InsertPoint;
				(*InsertPoint) = static_cast<char>(PlusValueAccess[2]);
				++InsertPoint;
				(*InsertPoint) = static_cast<char>(PlusValueAccess[1]);

				//c;オフセット適用
				InsertPoint = InsertTopPoint + Offset_first;

				//c:入力位置を進める。
				ConvertStr += bitcnt;
				//c:使用サイズカウント
				cnt += Offset_first;
				continue;
			};

		};

		memcpy(InsertPoint, ConvertStr, bitcnt);

		InsertPoint += bitcnt;
		ConvertStr += bitcnt;
		cnt += bitcnt;
	};//end while

	(*InsertPoint) = 0x00;
	++cnt;

	if( dst == nullptr )
	{
		UsedSize = cnt;
		delete[] buffer;
		return true;
	};

	//c:再度適切な配列サイズを作り直してもう一度コピー
	if( UsedSize < cnt )
	{
		//c:容量足りない。
		delete[] buffer;
		return false;
	};

	memcpy(dst, buffer, UsedSize);
	delete[] buffer;

	UsedSize = cnt;
	return true;
};


//==========================================
//========    StringControl    =============
//==========================================
bool SonikLibStringControl::StringPointEraser(char* ControlStr, uint64_t StartPoint, uint64_t EndPoint, uint64_t MaxStrCnt)
{
	if( StartPoint == 0 )
	{
		StartPoint = 1;
	};

	if( EndPoint == 0 )
	{
		EndPoint = MaxStrCnt;
	};

	if( EndPoint > MaxStrCnt )
	{
		return false;
	};

	if( StartPoint > MaxStrCnt )
	{
		return false;
	};

	//c:ポイントの捜索
	SonikLibConvertType Type_ = SonikLibStringConvert::CheckConvertType(ControlStr);
	uint64_t cnt = 0;
	uint64_t endcnt = MaxStrCnt+1;
	uint64_t OffsetCnt = 1;
	uint64_t bitcnt = 0;
	unsigned char swapbit = 0;
	unsigned char* pCheckSrc = reinterpret_cast<unsigned char*>(ControlStr);

	uintptr_t StartPointAddress = 0;
	uintptr_t EndPointAddress = 0;

	if( Type_ == SCHTYPE_SJIS )
	{
		while( (*pCheckSrc) != 0x00 )
		{
			OffsetCnt = 1;

			if( (0x80 <= (*pCheckSrc) && (*pCheckSrc) <= 0x9F) ||  (0xE0 <= (*pCheckSrc) && (*pCheckSrc) <= 0xFC) )
			{
				++OffsetCnt;
			};

			++cnt;

			if( cnt == StartPoint )
			{
				StartPointAddress = reinterpret_cast<uintptr_t>(pCheckSrc);
				endcnt = cnt + EndPoint -1;
			};

			if( cnt == endcnt )
			{
				EndPointAddress = reinterpret_cast<uintptr_t>(pCheckSrc);
//				EndPoint -= sizeof(uint8_t);
			};

			pCheckSrc += OffsetCnt;

		};

	}else if( Type_ == SCHTYPE_UTF8 )
	{
		while( static_cast<unsigned char>((*pCheckSrc)) != 0x00 )
		{
			swapbit = (*pCheckSrc);
			swapbit = SonikMathBit::BitSwapFor8bit(swapbit);

			bitcnt =  ~(swapbit);

			bitcnt |= (bitcnt << 1);
			bitcnt |= (bitcnt << 2);
			bitcnt |= (bitcnt << 4);
			bitcnt |= (bitcnt << 8);
			bitcnt |= (bitcnt << 16);
			bitcnt |= (bitcnt << 32);

			bitcnt = (bitcnt & 0x5555555555555555) + ( (bitcnt >> 1) & 0x5555555555555555 );
			bitcnt = (bitcnt & 0x3333333333333333) + ( (bitcnt >> 2) & 0x3333333333333333 );
			bitcnt = (bitcnt & 0x0F0F0F0F0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F0F0F0F0F );
			bitcnt = (bitcnt & 0x00FF00FF00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF00FF00FF );
			bitcnt = (bitcnt & 0x0000FFFF0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF0000FFFF );

			bitcnt = (bitcnt & 0x00000000FFFFFFFF) + ( (bitcnt >> 32) & 0x00000000FFFFFFFF);
			bitcnt = (64 - bitcnt);

			if( bitcnt == 0 )
			{
				++bitcnt;
			};

			++cnt;

			if( cnt == StartPoint )
			{
				StartPointAddress = reinterpret_cast<uintptr_t>(pCheckSrc);
				endcnt = cnt + EndPoint -1;
			};

			pCheckSrc += bitcnt;

			if( cnt == endcnt )
			{
				EndPointAddress = reinterpret_cast<uintptr_t>(pCheckSrc);
//				EndPoint -= sizeof(uint8_t);
			};

		};

	}else
	{
		return false;
	};

	if( EndPointAddress == 0 || StartPointAddress == 0 )
	{
		return false;
	};

	uint64_t movesize = reinterpret_cast<uintptr_t>(pCheckSrc) - EndPointAddress;
	memmove(reinterpret_cast<void*>(StartPointAddress), reinterpret_cast<void*>(EndPointAddress), movesize);

	movesize = EndPointAddress - StartPointAddress; //c:変数使い回し。
	EndPointAddress = reinterpret_cast<uintptr_t>(pCheckSrc) - (EndPointAddress - StartPointAddress);
	memset(reinterpret_cast<void*>(EndPointAddress), 0, movesize);

	return true;
};


#endif


