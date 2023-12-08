/*
 * SonikString.cpp
 *
 *  Created on: 2019/02/10
 *      Author: SONIK
 */

#ifdef __SONIK_I686__
//64bit definition
#include <new>
#include <algorithm>
#include <cstring>
#include <locale.h>
#include <cstdint>
#include "SonikString.h"
#include "..//SonikCASUse.h"
#include "..//SonikMathBitsUse.h"

namespace SonikLib
{
	//UTF8, UTF16, SJISが扱えるstringクラスです。
	//処理自体はスレッドセーフですが、文字列をgetした後にバッファを書き換えられる恐れがあります。
	class SonikString::SonikString_pImpl
	{
	private:
		//文字列領域
		uint8_t* Stringval_;

		//c:格納している最大文字数
		uint32_t MaxLength_;

		//現在の文字列のタイプ
		SonikLibConvertType CType;
		//文字列領域のサイズ
		uint32_t buffer_;
		//マルチスレッドブロック
		SonikLib::SonikAtomicLock string_atm_lock;
		//マルチスレッドブロック（オペレータ)
		SonikLib::SonikAtomicLock string_operator_lock;

	private:
		//内部用リサイズ関数です。
		bool ReAlloc(uint32_t ReSize);

		//現在のバッファタイプを指定のバッファタイプに変更します。
		//変更の際に、バッファに対して変換作業が行われます。
		//変換の際に失敗した場合は、falseになり、タイプの切り替えと変換作業は行われません。
		//SCHTYPE_UNKNOWNを指定した場合は、必ずfalseとなります。
		bool SetCharacterType(SonikLibConvertType SetType);

	public:
		//コンストラクタ
		SonikString_pImpl(void);
		//コンストラクタオーバーロード
		SonikString_pImpl(const char* SetStr);
		//コンストラクタオーバーロード
		SonikString_pImpl(const char16_t* SetStr);

		//コピーコンストラクタ
		SonikString_pImpl(const SonikString_pImpl& t_his);
		//ムーブコンストラクタ
		SonikString_pImpl(SonikString_pImpl&& Move);

		//デストラクタ
		~SonikString_pImpl(void);


		//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
		const char* c_str(void);
		//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
		const char16_t* c_wcstr(void);
		//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
		const char* utf8_str(void);

		//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint32_t GetCpy_c_str(char* dstBuffer = nullptr);
		//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint32_t GetCpy_c_wcstr(char16_t* dstBuffer = nullptr);
		//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint32_t GetCpy_utf8_str(char* dstBuffer = nullptr);

		//c:文字列のByte数を取得します。（Null終端文字をカウントに含まない)
		uint32_t Count_Byte_NotNull(void);
		//c:文字列数を取得します。（Null終端文字をカウントに含まない)
		uint32_t Count_Str_NotNull(void);

		//文字列中の全角英数字を半角英数字に変換します。
		bool ConvertFWANtoHWAN(void);
		//文字列中の全角カナを半角カナに変換します。
		bool ConvertFWKNtoHWKN(void);

		//c: 指定位置の文字を削除します。
		void EraseChar(uint64_t ChrPoint);
		//c: 指定の開始位置から指定された文字数を削除します。
		void EraseStr(uint64_t ChrStartPoint, uint64_t ChrEndPoint);

		//指定したAsciiコードをデリミタとしてSplitを行います。
		bool SplitForUTF8(uint8_t delim, SonikLib::SonikVariableArrayContainer<SonikLib::SonikString>& Container);


		//各入力フォーマットから現在のバッファに変換して代入します。
		SonikString_pImpl& operator =(const SonikString_pImpl& t_his);
		SonikString_pImpl& operator =(SonikString_pImpl&& Move);
		SonikString_pImpl& operator =(const char* Str);
		SonikString_pImpl& operator =(const char16_t* w_Str);

		//各入力フォーマットから現在のバッファに変換して結合します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString_pImpl& operator +=(const SonikString_pImpl& t_his);
		SonikString_pImpl& operator +=(const char* Str);
		SonikString_pImpl& operator +=(const char16_t* w_Str);

		//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString_pImpl operator +(const SonikString_pImpl& t_his);
		SonikString_pImpl operator +(const char* Str);
		SonikString_pImpl operator +(const char16_t* w_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 一致の場合true 不一致の場合 falseを返却します。
		bool operator ==(const SonikString_pImpl& t_his);
		bool operator ==(const char* Str);
		bool operator ==(const char16_t* w_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 不一致の場合true　一致の場合 falseを返却します。
		bool operator !=(const SonikString_pImpl& t_his);
		bool operator !=(const char* Str);
		bool operator !=(const char16_t* w_Str);

		//c:比較演算子
		bool Greater(const char* CompareArg2val);
		bool Less(const char* CompareArg2val);
		bool GreaterEqual(const char* CompareArg2val);
		bool LessEqual(const char* CompareArg2val);
	};


	SonikString::SonikString_pImpl::SonikString_pImpl(void)
	:MaxLength_(0)
	{
		Stringval_ = 0;
		buffer_ = 100;
		CType = SCHTYPE_NULLTEXT;

		try
		{
			Stringval_ = new uint8_t[buffer_];
		}catch(std::bad_alloc& e)
		{
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);
	};

	SonikString::SonikString_pImpl::SonikString_pImpl(const char* SetStr)
	{
		buffer_ = 100;
		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(SetStr);

		//NULL文字文追加(+1)して格納
		uint32_t SrcByte = SonikLibStringConvert::GetStringLengthByte(SetStr) + 1;

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			Stringval_ = new uint8_t[buffer_];
		}catch(std::bad_alloc& e)
		{
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));


		CType = tmpType;

	};

	SonikString::SonikString_pImpl::SonikString_pImpl(const char16_t* SetStr)
	{
		buffer_ = 100;
		CType = SCHTYPE_UTF16;

		uint32_t SrcLen = SonikLibStringConvert::GetStringLengthByte(SetStr);

		if(buffer_ < SrcLen)
		{
			buffer_ = SrcLen;
		};

		try
		{
			Stringval_ = new uint8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcLen);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));
	};

	SonikString::SonikString_pImpl::SonikString_pImpl(const SonikString_pImpl& t_his)
	{
		buffer_ = t_his.buffer_;
		CType = t_his.CType;
		MaxLength_ = t_his.MaxLength_;

		try
		{
			Stringval_ = new uint8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			throw;
		};

		memcpy(Stringval_, t_his.Stringval_, buffer_);

	};

	SonikString::SonikString_pImpl::SonikString_pImpl(SonikString_pImpl&& Move)
	{
		buffer_ = std::move(Move.buffer_);
		CType = std::move(Move.CType);
		Stringval_ = std::move(Move.Stringval_);
		MaxLength_ = std::move(Move.MaxLength_);

		Move.CType = SonikLibConvertType::SCHTYPE_UNKNOWN;
		Move.Stringval_ = nullptr;
		Move.buffer_ = 0;

	};

	SonikString::SonikString_pImpl::~SonikString_pImpl(void)
	{
		if(Stringval_ != 0)
		{
			delete[] Stringval_;
		};
	};

	//現在のバッファタイプを指定のバッファタイプに変更します。
	//変更の際に、バッファに対して変換作業が行われます。
	//変換の際に失敗した場合は、falseになり、タイプの切り替えと変換作業は行われません。
	bool SonikString::SonikString_pImpl::SetCharacterType(SonikLibConvertType SetType)
	{
		string_atm_lock.lock();

		uint32_t convSize_ = 0;
		switch(CType)
		{
		case SCHTYPE_SJIS:
			//SJIS から SetType へ各変換
			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//SJISへの変換は行わない。行う必要がない
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF16への変換
				SonikLibStringConvert::ConvertMBStoUTF16(reinterpret_cast<char*>(Stringval_), 0, &convSize_);


				if( (convSize_ +1) > buffer_ )
				{
					if( !this->ReAlloc( (convSize_+1) ) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertMBStoUTF16(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char16_t*>(Stringval_), &buffer_) )
				{
					string_atm_lock.Unlock();
					return false;
				};


				CType = SetType;
				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_UTF8:
				//SJISからUTF8への変換を行う。
				SonikLibStringConvert::ConvertMBSToUTF8(reinterpret_cast<char*>(Stringval_), 0, &convSize_);


				if( (convSize_ +1) > buffer_ )
				{
					if( !this->ReAlloc( (convSize_ +1) ) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertMBSToUTF8(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(Stringval_), &convSize_) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.Unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定
				break;
			};

			break;

		case SCHTYPE_UTF16:
			//UTF16  から SetType へ各変換
			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//UTF16からSJISへの変換
				SonikLibStringConvert::ConvertUTF16toMBS(reinterpret_cast<char16_t*>(Stringval_), 0, &convSize_);

				if( (convSize_ & 0x01) == 1 )
				{
					++convSize_;
				};

				if( (convSize_) > buffer_ )
				{
					if( !this->ReAlloc(convSize_) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF16toMBS(reinterpret_cast<char16_t*>(Stringval_), reinterpret_cast<char*>(Stringval_), &convSize_) )
				{
					string_atm_lock.Unlock();
					return false;
				};


				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF16 から UTF16への変換は行わない。行う必要がない。

				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_UTF8:
				//UTF16 から UTF8への変換
				SonikLibStringConvert::ConvertUTF16ToUTF8(reinterpret_cast<char16_t*>(Stringval_), 0, &convSize_);

				if( (convSize_ & 0x01) == 1 )
				{
					++convSize_;
				};

				if( (convSize_ +1) > buffer_ )
				{
					if( !this->ReAlloc(convSize_ +1) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF16ToUTF8(reinterpret_cast<char16_t*>(Stringval_), reinterpret_cast<char*>(Stringval_), &convSize_) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.Unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定

				string_atm_lock.Unlock();
				break;
			};

			break;

		case SCHTYPE_UTF8:

			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//UTF8からSJISへの変換
				SonikLibStringConvert::ConvertUTF8ToMBS(reinterpret_cast<char*>(Stringval_), 0, &convSize_);

				if( (convSize_ & 0x01) == 1 )
				{
					++convSize_;
				};

				if( (convSize_+1) > buffer_ )
				{
					if( !this->ReAlloc(convSize_ +1) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF8ToMBS(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(Stringval_), &convSize_) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF8からUTF16へ変換
				SonikLibStringConvert::ConvertUTF8ToUTF16(reinterpret_cast<char*>(Stringval_), 0, &convSize_);


				if( (convSize_ +2) > buffer_ )
				{
					if( !this->ReAlloc(convSize_ +2) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};


				if( !SonikLibStringConvert::ConvertUTF8ToUTF16(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char16_t*>(Stringval_), &convSize_) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF8:
				//UTF8からUTF8へ変換は行わない。行う必要がない。

				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.Unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定

				break;
			};

			break;

		case SCHTYPE_NULLTEXT:

			CType = SetType;
			string_atm_lock.Unlock();
			break;

		default:
			//SCHTYPE_UNKNOWN判定

			break;
		};

		string_atm_lock.Unlock();
		return false;
	};

	bool SonikString::SonikString_pImpl::ReAlloc(uint32_t ReArraySize)
	{
		uint8_t* pTmp = 0;


		pTmp = new(std::nothrow) uint8_t[ReArraySize];

		std::fill_n(pTmp, ReArraySize, 0);

		memcpy_s(pTmp, ReArraySize, Stringval_, buffer_);

		delete[] Stringval_;
		Stringval_ = pTmp;
		buffer_ = ReArraySize;

		return true;
	};

	const char* SonikString::SonikString_pImpl::c_str(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return "";
		};

		if( !this->SetCharacterType(SCHTYPE_SJIS) )
		{
			return "";
		};

		return reinterpret_cast<char*>(Stringval_);

	};

	const char16_t* SonikString::SonikString_pImpl::c_wcstr(void)
	{
		if( CType == SCHTYPE_UNKNOWN )
		{
			return u"";
		};

		if( !this->SetCharacterType(SCHTYPE_UTF16) )
		{
			return u"";
		};

		return reinterpret_cast<char16_t*>(Stringval_);

	};

	const char* SonikString::SonikString_pImpl::utf8_str(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return "";
		};

		if( !this->SetCharacterType(SCHTYPE_UTF8) )
		{
			return "";
		};

		return reinterpret_cast<char*>(Stringval_);
	};

	uint32_t SonikString::SonikString_pImpl::GetCpy_c_str(char* dstBuffer)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return 0;
		};

		if(CType != SCHTYPE_SJIS)
		{
			//UNKNOWN以外　かつ SJIS以外ならSJISへ変換してカウントチェック
			if( !this->SetCharacterType(SCHTYPE_SJIS) )
			{
				return 0;
			};
		};

		//NULL文字分追加 (+1)して格納
		uint32_t cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_))  + 1;

		if( dstBuffer == 0 || dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	uint32_t SonikString::SonikString_pImpl::GetCpy_c_wcstr(char16_t* dstBuffer)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return 0;
		};

		if(CType != SCHTYPE_UTF16)
		{
			//UNKNOWN以外　かつ UTF16以外ならUTF16へ変換してカウントチェック
			if( !this->SetCharacterType(SCHTYPE_UTF16) )
			{
				return 0;
			};
		};

		//NULL文字分追加(wide = +2) して格納
		uint32_t cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_)) + 2;

		if( dstBuffer == 0 || dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	uint32_t SonikString::SonikString_pImpl::GetCpy_utf8_str(char* dstBuffer)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return 0;
		};

		if(CType != SCHTYPE_UTF8)
		{
			//UNKNOWN以外　かつ UTF8以外ならUTF8へ変換してカウントチェック
			if( !this->SetCharacterType(SCHTYPE_UTF8) )
			{
				return 0;
			};
		};

		//NULL文字分追加 (+1)して格納
		uint32_t cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_)) + 1;

		if( dstBuffer == 0 || dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	//c:文字列のByte数を取得します。（Null終端文字をカウントに含まない)
	uint32_t SonikString::SonikString_pImpl::Count_Byte_NotNull(void)
	{
		return SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
	};

	//c:文字列数を取得します。（Null終端文字をカウントに含まない)
	uint32_t SonikString::SonikString_pImpl::Count_Str_NotNull(void)
	{
		return MaxLength_;
	};

	//文字列中の全角英数字を半角英数字に変換します。
	bool SonikString::SonikString_pImpl::ConvertFWANtoHWAN(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return false;
		};

		//全角半角変換はUTF-8しか作ってないのでUTF-8に一度変換する。
		if( !this->SetCharacterType(SCHTYPE_UTF8) )
		{
			return false;
		};

		string_atm_lock.lock();
		//全角半角変換
		uint32_t Size = 0;
		//サイズ取得
		SonikLibStringConvert::ConvertUTF8FWCToHWCForAN(reinterpret_cast<char*>(Stringval_), nullptr, Size);
		//領域取得
		if( Size & 0x01 )
		{
			++Size;
		};

		uint8_t* tmp_Str = new(std::nothrow) uint8_t[Size];
		if( tmp_Str == nullptr || tmp_Str == 0 )
		{
			string_atm_lock.Unlock();
			return false;
		};

		//本番
		if( !SonikLibStringConvert::ConvertUTF8FWCToHWCForAN(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(tmp_Str), Size) )
		{
			string_atm_lock.Unlock();
			return false;
		};

		delete Stringval_;
		Stringval_ = tmp_Str;

		if( buffer_ < Size )
		{
			buffer_ = Size;
		};

		string_atm_lock.Unlock();
		return true;
	};

	//文字列中の全角カナを半角カナに変換します。
	bool SonikString::SonikString_pImpl::ConvertFWKNtoHWKN(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return false;
		};

		//全角半角変換はUTF-8しか作ってないのでUTF-8に一度変換する。
		if( !this->SetCharacterType(SCHTYPE_UTF8) )
		{
			return false;
		};

		string_atm_lock.lock();
		//全角半角変換
		uint32_t Size = 0;
		//サイズ取得
		SonikLibStringConvert::ConvertUTF8FWCToHWCForKANA(reinterpret_cast<char*>(Stringval_), nullptr, Size);
		//領域取得
		if( Size & 0x01 )
		{
			++Size;
		};

		uint8_t* tmp_Str = new(std::nothrow) uint8_t[Size];
		if( tmp_Str == nullptr || tmp_Str == 0 )
		{
			string_atm_lock.Unlock();
			return false;
		};

		//本番
		if( !SonikLibStringConvert::ConvertUTF8FWCToHWCForKANA(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(tmp_Str), Size) )
		{
			string_atm_lock.Unlock();
			return false;
		};

		delete Stringval_;
		Stringval_ = reinterpret_cast<uint8_t*>(tmp_Str);

		if( buffer_ < Size )
		{
			buffer_ = Size;
		};

		string_atm_lock.Unlock();

		return true;
	};

	//c: 指定位置の文字を削除します。
	void SonikString::SonikString_pImpl::EraseChar(uint64_t ChrPoint)
	{
		this->utf8_str();

		if( SonikLibStringControl::StringPointEraser(reinterpret_cast<char*>(Stringval_), ChrPoint, 1, MaxLength_) )
		{
			MaxLength_ -= 1;
		};

	};

	//c: 指定の開始位置から指定された文字数を削除します。
	void SonikString::SonikString_pImpl::EraseStr(uint64_t ChrStartPoint, uint64_t ChrEndPoint)
	{
		this->utf8_str();

		if( SonikLibStringControl::StringPointEraser(reinterpret_cast<char*>(Stringval_), ChrStartPoint, ChrEndPoint, MaxLength_) )
		{
			MaxLength_ -= ChrEndPoint;
		};
	};


	bool SonikString::SonikString_pImpl::SplitForUTF8(uint8_t delim, SonikLib::SonikVariableArrayContainer<SonikLib::SonikString>& Container)
	{
		this->utf8_str();

		uint32_t bitcnt = 0;
		unsigned char swapbit = 0;
		uint8_t* pTmpstr = reinterpret_cast<uint8_t*>(Stringval_);
		uint8_t* pTmpstr_St = pTmpstr;
		SonikLib::SonikString PushStr;
		while( (*pTmpstr) != 0x00 )
		{
			swapbit = (*pTmpstr);
			swapbit = SonikMathBit::BitSwapFor8bit(swapbit);

			bitcnt =  ~(swapbit);

			bitcnt |= (bitcnt << 1);
			bitcnt |= (bitcnt << 2);
			bitcnt |= (bitcnt << 4);
			bitcnt |= (bitcnt << 8);
			bitcnt |= (bitcnt << 16);

			bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
			bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
			bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
			bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );

			bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
			bitcnt = (32 - bitcnt);

			if( bitcnt == 0 )
			{
				++bitcnt;
			};


			if( (*pTmpstr) == delim )
			{
				(*pTmpstr) = 0;
				PushStr = reinterpret_cast<char*>(pTmpstr_St);
				if( !Container.PushBack(PushStr) )
				{
					(*pTmpstr) = delim;
					return false;
				};

				(*pTmpstr) = delim;
				pTmpstr_St = pTmpstr;
				++pTmpstr_St;
			};

			pTmpstr += bitcnt;

		};

		PushStr = reinterpret_cast<char*>(pTmpstr_St);
		if( !Container.PushBack(PushStr) )
		{
			(*pTmpstr) = delim;
			return false;
		};

		return true;
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(const SonikString_pImpl& t_his)
	{
		buffer_ = t_his.buffer_;
		CType = t_his.CType;
		MaxLength_ = t_his.MaxLength_;

		if( this == &t_his )
		{
			return (*this);
		};

		if( Stringval_ != 0 )
		{
			delete[] Stringval_;

		};

		try
		{
			Stringval_ = new uint8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			throw;
		};

		memcpy(Stringval_, t_his.Stringval_, buffer_);

		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(SonikString_pImpl&& Move)
	{
		if( this == &Move )
		{
			return (*this);
		};

		if( Stringval_ != 0 )
		{
			delete[] Stringval_;

		};

		buffer_ = std::move(Move.buffer_);
		CType = std::move(Move.CType);
		Stringval_ = std::move(Move.Stringval_);
		MaxLength_ = std::move(Move.MaxLength_);

		Move.CType = SonikLibConvertType::SCHTYPE_UNKNOWN;
		Move.Stringval_ = nullptr;
		Move.buffer_ = 0;

		return (*this);

	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(const char* Str)
	{
		if(Str == 0 )
		{
			return (*this);
		};

		string_operator_lock.lock();

		std::fill_n(Stringval_, buffer_, 0);
		if( strcmp(Str, "") == 0 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.Unlock();
			return (*this);
		};

		CType = SonikLibStringConvert::CheckConvertType(Str);
		uint32_t Size_ = SonikLibStringConvert::GetStringLengthByte(Str);


		if(buffer_ < (Size_ + 1))
		{
			//null終端分追加
			this->ReAlloc( Size_ +1 );
		};

		memcpy_s(Stringval_, buffer_ , Str, Size_);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		string_operator_lock.Unlock();
		return (*this);

	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(const char16_t* w_Str)
	{
		if(w_Str == 0 )
		{
			return (*this);
		};

		string_operator_lock.lock();

		std::fill_n(Stringval_, buffer_, 0);
		if( (*w_Str) == 0x00 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.Unlock();
			return (*this);
		};

		CType = SCHTYPE_UTF16;
		uint32_t Size_ = SonikLibStringConvert::GetStringLengthByte(w_Str);

		if( (Size_ +2) > buffer_ )
		{
			this->ReAlloc(Size_ + 2);
		};

		memcpy_s(Stringval_, buffer_, w_Str, Size_);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));

		string_operator_lock.Unlock();
		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator +=(const SonikString_pImpl& t_his)
	{
		string_operator_lock.lock();

		if( t_his.CType == SCHTYPE_NULLTEXT || t_his.CType == SCHTYPE_UNKNOWN )
		{
			//c:結合を行わない
			string_operator_lock.Unlock();
			return (*this);
		};

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。
		if( CType != t_his.CType )
		{
			SetCharacterType(t_his.CType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint32_t CopySize_;
		uint32_t bufuse_;
		uint32_t sizeofsize_ = 0;
		if(t_his.CType == SCHTYPE_UTF16)
		{
			// >> 1 = x/2
			CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(t_his.Stringval_));
			bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));

			if( buffer_ < (CopySize_ + bufuse_ ))
			{
				this->ReAlloc((CopySize_ + bufuse_) + 2);
			};

			sizeofsize_ = 2;

		}else
		{

			CopySize_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(t_his.Stringval_));
			bufuse_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

			if( buffer_ < (CopySize_ + bufuse_) + 1 )
			{
				this->ReAlloc((CopySize_ + bufuse_) + 1);
			};

			sizeofsize_ = 1;

		};

		CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
		bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + sizeofsize_), t_his.Stringval_, CopySize_);

		if( CType == SCHTYPE_UTF16 )
		{
			MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));
		}else
		{
			MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		};


		//最後に全部元の形に変換
//		SetCharacterType(CType);

		string_operator_lock.Unlock();
		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator +=(const char* Str)
	{
		string_operator_lock.lock();

		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(Str);

		if(tmpType == SCHTYPE_UTF16)
		{
			//reinterpret_castなどで変換して渡された場合に検出する可能性あり。
			string_atm_lock.Unlock();
			return (*this);
		};

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。
		if( CType != tmpType )
		{
			SetCharacterType(tmpType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint32_t CopySize_ = SonikLibStringConvert::GetStringLengthByte(Str);
		uint32_t bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

		if( (CopySize_ + bufuse_) > buffer_ )
		{
			this->ReAlloc( (CopySize_ + bufuse_) + 1);
		};

		CopySize_ = SonikLibStringConvert::GetStringLengthByte(Str);
		bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 1) , Str, CopySize_ );
		Stringval_[bufuse_ + CopySize_] = 0;
		//最後に全部コピー元の形に変換
//		SetCharacterType(CType);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		string_operator_lock.Unlock();
		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator +=(const char16_t* w_Str)
	{
		string_operator_lock.lock();

		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<char*>(const_cast<char16_t*>(w_Str)));

		if(tmpType == SCHTYPE_UTF8 || tmpType == SCHTYPE_SJIS)
		{
			//reinterpret_castなどで変換して渡された場合に検出する可能性あり。
			string_operator_lock.Unlock();
			return (*this);
		};

		tmpType = SCHTYPE_UTF16;
		//コピー元とタイプが違えばコピー元に合わせて変換をかける。(ここではUTF16確定になる)
		if( CType != tmpType )
		{
			SetCharacterType(tmpType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint32_t CopySize_ = SonikLibStringConvert::GetStringLengthByte(w_Str);
		uint32_t bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));

		if( (CopySize_ + bufuse_) + 2 > buffer_ )
		{
			this->ReAlloc( (CopySize_ + bufuse_) + 2);
		};

//		CopySize_ = SonikLibStringConvert::GetStringLengthByte(w_Str);
//		bufuse_ = SonikLibStringConvert::GetStringLengthByte(Stringval_);

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 2), w_Str, CopySize_);
		Stringval_[bufuse_ + CopySize_] = 0;

		//utf8の残骸が後ろに残っている可能性があるので、0を直接埋め込む
		Stringval_[bufuse_ + CopySize_ + 1] = 0;

		//最後に全部コピー元の形に変換
//		SetCharacterType(CType);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));

		string_operator_lock.Unlock();
		return (*this);
	};

	//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikString::SonikString_pImpl SonikString::SonikString_pImpl::operator +(const SonikString_pImpl& t_his)
	{
		SonikString_pImpl tmpStr = (*this);

		tmpStr += t_his;

		return tmpStr;
	};

	SonikString::SonikString_pImpl SonikString::SonikString_pImpl::operator +(const char* Str)
	{
		SonikString_pImpl tmpStr = (*this);

		tmpStr += Str;

		return tmpStr;
	};

	SonikString::SonikString_pImpl SonikString::SonikString_pImpl::operator +(const char16_t* w_Str)
	{
		SonikString_pImpl tmpStr = (*this);

		tmpStr += w_Str;

		return tmpStr;

	};

	//c: 文字列同士を比較します。(strcmp)
	//c: 一致の場合true 不一致の場合 falseを返却します。
	bool SonikString::SonikString_pImpl::operator ==(const SonikString_pImpl& t_his)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != t_his.CType )
		{
			if( !SetCharacterType(t_his.CType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint32_t myuse_ = 0;
		uint32_t targetuse_ = 0;
		if( CType == SCHTYPE_UTF16 )
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(t_his.Stringval_));

		}else
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
		};

		//c: サイズが一緒なら次の精査へ
		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint32_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != t_his.Stringval_[i] )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	bool SonikString::SonikString_pImpl::operator ==(const char* Str)
	{
		SonikLibConvertType StrType = SonikLibStringConvert::CheckConvertType(Str);

		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != StrType )
		{
			if( !SetCharacterType(StrType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint32_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
		uint32_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(Str);

		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint32_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != Str[i] )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	bool SonikString::SonikString_pImpl::operator ==(const char16_t* w_Str)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != SCHTYPE_UTF16 )
		{
			if( !SetCharacterType(SCHTYPE_UTF16) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint32_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
		uint32_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(w_Str);

		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint32_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != w_Str[i] )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	//c: 文字列同士を比較します。(strcmp)
	//c: 不一致の場合true　一致の場合 falseを返却します。
	bool SonikString::SonikString_pImpl::operator !=(const SonikString_pImpl& t_his)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != t_his.CType )
		{
			if( !SetCharacterType(t_his.CType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint32_t myuse_ = 0;
		uint32_t targetuse_ = 0;
		if( CType == SCHTYPE_UTF16 )
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(t_his.Stringval_));

		}else
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
		};

		//c: サイズが一緒なら次の精査へ
		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint32_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != t_his.Stringval_[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	bool SonikString::SonikString_pImpl::operator !=(const char* Str)
	{
		SonikLibConvertType StrType = SonikLibStringConvert::CheckConvertType(Str);

		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != StrType )
		{
			if( !SetCharacterType(StrType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint32_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
		uint32_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(Str);

		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint32_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != Str[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	bool SonikString::SonikString_pImpl::operator !=(const char16_t* w_Str)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != SCHTYPE_UTF16 )
		{
			if( !SetCharacterType(SCHTYPE_UTF16) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint32_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
		uint32_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(w_Str);

		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint32_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != w_Str[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	//c:比較演算子
	bool SonikString::SonikString_pImpl::Greater(const char* CompareArg2val)
	{
		if( strcmp(this->c_str(), CompareArg2val) < 0 )
		{
			return true;
		};

		return false;
	};

	bool SonikString::SonikString_pImpl::Less(const char* CompareArg2val)
	{
		return this->Greater(CompareArg2val);
	};

	bool SonikString::SonikString_pImpl::GreaterEqual(const char* CompareArg2val)
	{
		return !(this->Less(CompareArg2val));
	};

	bool SonikString::SonikString_pImpl::LessEqual(const char* CompareArg2val)
	{
		return !(this->Greater(CompareArg2val));
	};
//===========================================================
//
//				pImpl使用（外側)クラスの実装
//
//===========================================================

	SonikString::SonikString(void)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
		}catch(std::bad_alloc&)
		{
			throw;
		};

	};
	SonikString::SonikString(const SonikString& t_his)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
			(*pImpl) = (*(t_his.pImpl));
		}catch(std::bad_alloc&)
		{
			throw;
		};
	};

	SonikString::SonikString(const char* SetStr)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			throw;
		};
	};

	SonikString::SonikString(const char16_t* SetStr)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			throw;
		};
	};

	SonikString::SonikString(SonikString&& Move)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
			(*pImpl) = std::move( (*(Move.pImpl)) );
		}catch(std::bad_alloc&)
		{
			throw;
		};

	};

	SonikString::~SonikString(void)
	{
		if(pImpl != 0)
		{
			delete pImpl;
		};
	};

	//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
	const char* SonikString::c_str(void)
	{
		return pImpl->c_str();
	};

	//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
	const char16_t* SonikString::c_wcstr(void)
	{
		return pImpl->c_wcstr();
	};

	//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
	const char* SonikString::utf8_str(void)
	{
		return pImpl->utf8_str();
	};

	//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	uint32_t SonikString::GetCpy_c_str(char* dstBuffer)
	{
		return pImpl->GetCpy_c_str(dstBuffer);
	};

	//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	uint32_t SonikString::GetCpy_c_wcstr(char16_t* dstBuffer)
	{
		return pImpl->GetCpy_c_wcstr(dstBuffer);
	};

	//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	uint32_t SonikString::GetCpy_utf8_str(char* dstBuffer)
	{
		return pImpl->GetCpy_utf8_str(dstBuffer);
	};

	//c:文字列のByte数を取得します。（Null終端文字をカウントに含まない)
	uint32_t SonikString::Count_Byte_NotNull(void)
	{
		return pImpl->Count_Byte_NotNull();
	};

	//c:文字列数を取得します。（Null終端文字をカウントに含まない)
	uint32_t SonikString::Count_Str_NotNull(void)
	{
		return pImpl->Count_Str_NotNull();
	};

	//文字列中の全角英数字を半角英数字に変換します。
	bool SonikString::ConvertFWANtoHWAN(void)
	{
		return pImpl->ConvertFWANtoHWAN();
	};

	//文字列中の全角カナを半角カナに変換します。
	bool SonikString::ConvertFWKNtoHWKN(void)
	{
		return pImpl->ConvertFWKNtoHWKN();
	};

	//c: 指定位置の文字を削除します。
	void SonikString::EraseChar(uint32_t ChrPoint)
	{
		pImpl->EraseChar(ChrPoint);
	};

	//c: 指定の開始位置から指定された文字数を削除します。
	void SonikString::EraseStr(uint32_t ChrStartPoint, uint32_t ChrEndPoint)
	{
		pImpl->EraseStr(ChrStartPoint, ChrEndPoint);
	};

	//指定したAsciiコードをデリミタとしてSplitを行います。
	bool SonikString::SplitForUTF8(uint8_t delim, SonikLib::SonikVariableArrayContainer<SonikLib::SonikString>& Container)
	{
		return pImpl->SplitForUTF8(delim, Container);
	};

	//各入力フォーマットから現在のバッファに変換して代入します。
	SonikString& SonikString::operator =(const SonikString& t_his)
	{
		(*pImpl) = (*(t_his.pImpl));

		return (*this);
	};

	SonikString& SonikString::operator =(SonikString&& Move)
	{
		(*pImpl) = std::move( (*(Move.pImpl)) );

		return (*this);
	};

	SonikString& SonikString::operator =(const char* Str)
	{
		(*pImpl) = Str;

		return (*this);
	};

	SonikString& SonikString::operator =(const char16_t* w_Str)
	{
		(*pImpl) = w_Str;

		return (*this);
	};

	//各入力フォーマットから現在のバッファに変換して結合します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikString& SonikString::operator +=(const SonikString& t_his)
	{
		(*pImpl) += (*(t_his.pImpl));

		return (*this);
	};

	SonikString& SonikString::operator +=(const char* Str)
	{
		(*pImpl) += Str;

		return (*this);
	};

	SonikString& SonikString::operator +=(const char16_t* w_Str)
	{
		(*pImpl) += w_Str;

		return (*this);
	};

	//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikString SonikString::operator +(const SonikString& t_his)
	{
		SonikString str_;

		(*(str_.pImpl)) = (*pImpl) + (*(t_his.pImpl));

		return str_;
	};

	SonikString SonikString::operator +(const char* Str)
	{
		SonikString str_;

		(*(str_.pImpl)) = (*pImpl) + Str;

		return str_;
	};

	SonikString SonikString::operator +(const char16_t* w_Str)
	{
		SonikString str_;

		(*(str_.pImpl)) = (*pImpl) + w_Str;

		return str_;
	};

	bool operator <(const SonikString& CompareArg1val, const SonikString& CompareArg2val)
	{
		return CompareArg1val.pImpl->Greater(CompareArg2val.pImpl->c_str());
	};

	bool operator >(const SonikString& CompareArg1val, const SonikString& CompareArg2val)
	{
		return CompareArg1val.pImpl->Less(CompareArg2val.pImpl->c_str());
	};

	bool operator <=(const SonikString& CompareArg1val, const SonikString& CompareArg2val)
	{
		return CompareArg1val.pImpl->GreaterEqual(CompareArg2val.pImpl->c_str());
	};

	bool operator >=(const SonikString& CompareArg1val, const SonikString& CompareArg2val)
	{
		return CompareArg1val.pImpl->LessEqual(CompareArg2val.pImpl->c_str());
	};



};

#endif


