/*
 * SonikStringWIDE.h
 *
 *  Created on: 2016/01/10
 *      Author: SONIK
 *  TEXTFORMAT: UTF-8
 */

#ifndef __SONIKLIB_SONIKSTRING_WIDE_H__
#define __SONIKLIB_SONIKSTRING_WIDE_H__

#include "../SonikStringLocaleEnmus.h"

//C++20 以前はchar8_t が無いので。
#if __cplusplus < 202002L
    //C++20 以前であれば　char8_t は uint8_t
    using utf8_t = uint8_t;
#else
	#include <cuchar>
	using utf8_t = char8_t;

#endif


//前方宣言===================================
namespace SonikLib
{
	namespace Container
	{
		template <class T>
		class SonikVariableArrayContainer;
	};
};
//=========================================


namespace SonikLib
{
	class SonikStringWIDE
	{
		friend bool operator<(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);
		friend bool operator>(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);
		friend bool operator<=(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);
		friend bool operator>=(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);

	private:
		class SonikStringWIDE_pImpl;
		SonikStringWIDE_pImpl* pImpl;

	public:
		SonikStringWIDE(SonikLibStringConvert::SonikLibConvertLocale _setlocale_ = SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
		SonikStringWIDE(const SonikStringWIDE& t_his);
		SonikStringWIDE(const char* SetStr);
		SonikStringWIDE(const char* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringWIDE(const char16_t* SetStr);
		SonikStringWIDE(const char16_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringWIDE(const wchar_t* SetStr);
		SonikStringWIDE(const wchar_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringWIDE(const utf8_t* SetStr);
		SonikStringWIDE(const utf8_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const int8_t SetValue);
		SonikStringWIDE(const int8_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const uint8_t SetValue);
		SonikStringWIDE(const uint8_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const int16_t SetValue);
		SonikStringWIDE(const int16_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const uint16_t SetValue);
		SonikStringWIDE(const uint16_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const int32_t SetValue);
		SonikStringWIDE(const int32_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const uint32_t SetValue);
		SonikStringWIDE(const uint32_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const int64_t SetValue);
		SonikStringWIDE(const int64_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const uint64_t SetValue);
		SonikStringWIDE(const uint64_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const float SetValue);
		SonikStringWIDE(const float SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringWIDE(const double SetValue);
		SonikStringWIDE(const double SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);


		~SonikStringWIDE(void);

		//ロケールを設定します。
		bool SetStringLocale(SonikLibStringConvert::SonikLibConvertLocale _setlocale_);

		//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
		const char* str_c(void);
		//wchar_t形式に変換して取得します。(バッファタイプも書き換わります。)
		const wchar_t* str_wchar(void);
		//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
		const char16_t* str_utf16(void);
		//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
		const utf8_t* str_utf8(void);

		//define切り替えのstrゲット
		const wchar_t* definition_str(void);

		//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_c(char* dstBuffer = nullptr);
		//wchar_t形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_wcstr(wchar_t* dstBuffer = nullptr);
		//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_utf16(char16_t* dstBuffer = nullptr);
		//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_utf8(utf8_t* dstBuffer = nullptr);

		//define切り替えのStrCopy
		uint64_t GetCpy_str_definition(wchar_t* dstBuffer = nullptr);

		//c:文字列のByte数を取得します。（Null終端文字をカウントに含まない)
		uint64_t Count_Byte_NotNull(void);
		//c:文字列数を取得します。（Null終端文字をカウントに含まない)
		uint64_t Count_Str_NotNull(void);

		//文字列中の全角英数字を半角英数字に変換します。
		bool ConvertFWANtoHWAN(void);
		//文字列中の全角カナを半角カナに変換します。
		bool ConvertFWKNtoHWKN(void);

		//c: 指定位置の文字を削除します。
		void EraseChar(uint64_t ChrPoint);
		//c: 指定の開始位置から指定された文字数を削除します。
		void EraseStr(uint64_t ChrStartPoint, uint64_t ChrEndPoint);

		//指定したAsciiコードをデリミタとしてSplitを行います。
		bool SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringWIDE>& Container);

		//各入力フォーマットから現在のバッファに変換して代入します。
		SonikStringWIDE& operator =(const SonikStringWIDE& t_his);
		SonikStringWIDE& operator =(SonikStringWIDE&& Move) noexcept;
		SonikStringWIDE& operator =(const char* Str);
		SonikStringWIDE& operator =(const char16_t* w_Str);
		SonikStringWIDE& operator =(const wchar_t* w_Str);
		SonikStringWIDE& operator =(const utf8_t* utf8_Str);
        SonikStringWIDE& operator =(const int8_t SetValue);
        SonikStringWIDE& operator =(const uint8_t SetValue);
        SonikStringWIDE& operator =(const int16_t SetValue);
        SonikStringWIDE& operator =(const uint16_t SetValue);
        SonikStringWIDE& operator =(const int32_t SetValue);
        SonikStringWIDE& operator =(const uint32_t SetValue);
        SonikStringWIDE& operator =(const int64_t SetValue);
        SonikStringWIDE& operator =(const uint64_t SetValue);
        SonikStringWIDE& operator =(const float SetValue);
		SonikStringWIDE& operator =(const double SetValue);

		//各入力フォーマットから現在のバッファに変換して結合します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringWIDE& operator +=(const SonikStringWIDE& t_his);
		SonikStringWIDE& operator +=(const char* Str);
		SonikStringWIDE& operator +=(const char16_t* w_Str);
		SonikStringWIDE& operator +=(const wchar_t* w_Str);
		SonikStringWIDE& operator +=(const utf8_t* utf8_Str);
        SonikStringWIDE& operator +=(const int8_t SetValue);
        SonikStringWIDE& operator +=(const uint8_t SetValue);
        SonikStringWIDE& operator +=(const int16_t SetValue);
        SonikStringWIDE& operator +=(const uint16_t SetValue);
        SonikStringWIDE& operator +=(const int32_t SetValue);
        SonikStringWIDE& operator +=(const uint32_t SetValue);
        SonikStringWIDE& operator +=(const int64_t SetValue);
        SonikStringWIDE& operator +=(const uint64_t SetValue);
        SonikStringWIDE& operator +=(const float SetValue);
		SonikStringWIDE& operator +=(const double SetValue);

		//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringWIDE operator +(const SonikStringWIDE& t_his);
		SonikStringWIDE operator +(const char* Str);
		SonikStringWIDE operator +(const char16_t* w_Str);
		SonikStringWIDE operator +(const wchar_t* w_Str);
		SonikStringWIDE operator +(const utf8_t* utf8_Str);
        SonikStringWIDE operator +(const int8_t SetValue);
        SonikStringWIDE operator +(const uint8_t SetValue);
        SonikStringWIDE operator +(const int16_t SetValue);
        SonikStringWIDE operator +(const uint16_t SetValue);
        SonikStringWIDE operator +(const int32_t SetValue);
        SonikStringWIDE operator +(const uint32_t SetValue);
        SonikStringWIDE operator +(const int64_t SetValue);
        SonikStringWIDE operator +(const uint64_t SetValue);
        SonikStringWIDE operator +(const float SetValue);
		SonikStringWIDE operator +(const double SetValue);

		//c: 文字列同士を比較します。(strcmp)
		//c: 一致の場合true 不一致の場合 falseを返却します。
		bool operator ==(const SonikStringWIDE& t_his);
		bool operator ==(const char* Str);
		bool operator ==(const char16_t* w_Str);
		bool operator ==(const wchar_t* w_Str);
		bool operator ==(const utf8_t* utf8_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 不一致の場合true　一致の場合 falseを返却します。
		bool operator !=(const SonikStringWIDE& t_his);
		bool operator !=(const char* Str);
		bool operator !=(const char16_t* w_Str);
		bool operator !=(const wchar_t* w_Str);
		bool operator !=(const utf8_t* utf8_Str);

	};

	//c:比較演算子
	bool operator<(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);
	bool operator>(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);
	bool operator<=(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);
	bool operator>=(const SonikStringWIDE& CompareArg1val, const SonikStringWIDE& CompareArg2val);
};

#endif /* __SONIKLIB_SONIKSTRING_WIDE_H__ */
