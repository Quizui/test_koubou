/*
 * SonikString_UTF16.h
 *
 *  Created on: 2024/01/21
 *      Author: SONIC
 */

#ifndef SONIKSTRING_UTF16_SONIKSTRING_UTF16_H_
#define SONIKSTRING_UTF16_SONIKSTRING_UTF16_H_

#include "../../Container/RangedForContainer.hpp"

namespace SonikLib
{
	class SonikString_UTF16
	{
		friend bool operator<(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);
		friend bool operator>(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);
		friend bool operator<=(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);
		friend bool operator>=(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);

	private:
		class SonikString_UTF16_pImpl;
		SonikString_UTF16_pImpl* pImpl;

	public:
		SonikString_UTF16(void);
		SonikString_UTF16(const SonikString_UTF16& t_his);
		SonikString_UTF16(const char* SetStr);
		SonikString_UTF16(const char16_t* SetStr);
		SonikString_UTF16(const wchar_t* SetPtr);
		SonikString_UTF16(const uint8_t* SetStr);
		SonikString_UTF16(SonikString_UTF16&& Move) noexcept;

		~SonikString_UTF16(void);

		//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
		const char* c_str(void);
		//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
		const char16_t* c_wcstr(void);
		//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
		const uint8_t* utf8_str(void);

		//define切り替えのstrゲット
		const char16_t* definition_str(void);

		//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_c_str(char* dstBuffer = nullptr);
		//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_c_wcstr(char16_t* dstBuffer = nullptr);
		//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_c_wcstr(wchar_t* dstBuffer = nullptr);
		//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_utf8_str(char* dstBuffer = nullptr);

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
		bool SplitForUTF8(uint8_t delim, SonikLib::SonikVariableArrayContainer<SonikLib::SonikString_UTF16>& Container);

		//各入力フォーマットから現在のバッファに変換して代入します。
		SonikString_UTF16& operator =(const SonikString_UTF16& t_his);
		SonikString_UTF16& operator =(SonikString_UTF16&& Move) noexcept;
		SonikString_UTF16& operator =(const char* Str);
		SonikString_UTF16& operator =(const char16_t* w_Str);
		SonikString_UTF16& operator =(const wchar_t* w_Str);
		SonikString_UTF16& operator =(const uint8_t* utf8_Str);

		//各入力フォーマットから現在のバッファに変換して結合します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString_UTF16& operator +=(const SonikString_UTF16& t_his);
		SonikString_UTF16& operator +=(const char* Str);
		SonikString_UTF16& operator +=(const char16_t* w_Str);
		SonikString_UTF16& operator +=(const wchar_t* w_Str);
		SonikString_UTF16& operator +=(const uint8_t* utf8_Str);

		//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString_UTF16 operator +(const SonikString_UTF16& t_his);
		SonikString_UTF16 operator +(const char* Str);
		SonikString_UTF16 operator +(const char16_t* w_Str);
		SonikString_UTF16 operator +(const wchar_t* w_Str);
		SonikString_UTF16 operator +(const uint8_t* utf8_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 一致の場合true 不一致の場合 falseを返却します。
		bool operator ==(const SonikString_UTF16& t_his);
		bool operator ==(const char* Str);
		bool operator ==(const char16_t* w_Str);
		bool operator ==(const wchar_t* w_Str);
		bool operator ==(const uint8_t* utf8_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 不一致の場合true　一致の場合 falseを返却します。
		bool operator !=(const SonikString_UTF16& t_his);
		bool operator !=(const char* Str);
		bool operator !=(const char16_t* w_Str);
		bool operator !=(const wchar_t* w_Str);
		bool operator !=(const uint8_t* utf8_Str);

	};

	//c:比較演算子
	bool operator<(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);
	bool operator>(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);
	bool operator<=(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);
	bool operator>=(const SonikString_UTF16& CompareArg1val, const SonikString_UTF16& CompareArg2val);
};

#endif /* SONIKSTRING_UTF16_SONIKSTRING_UTF16_H_ */