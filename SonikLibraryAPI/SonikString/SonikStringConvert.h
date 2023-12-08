/*
 * SonikStringConvert.h
 *
 *  Created on: 2016/01/08
 *      Author: SONIK
 *  TEXTFORMAT: UTF-8
 */

#ifndef SONIKString_SONIKStringCONVERT_H_
#define SONIKString_SONIKStringCONVERT_H_

//#include "..\\SonikCASUse.h"
#include <cstdint>

enum SonikLibConvertType
{
	SCHTYPE_SJIS = 0,
	SCHTYPE_UTF8,
	SCHTYPE_BOMUTF8,
	SCHTYPE_UTF16,
	SCHTYPE_UNKNOWN,
	SCHTYPE_NULLTEXT,
};

namespace SonikLibStringConvert
{

#ifdef __SONIK_I686__
//32bit definition
	//文字列のタイプが、SJISかUTF-8かを判別します。
	//完全な判別は不可能（らしい）なので可能性の範囲でチェックされた結果を返却します。
	//ASCIIはSJISとして結果を返却します。
	//UTF-16 は返却値としては返りません。
	SonikLibConvertType CheckConvertType(const char* pCheckSrc);

	//文字列のタイプをチェックし、その文字列で使用されているバイト数を返却します。
	//文字列のタイプチェックは可能性の範囲のチェックとなります。
	//SJIS, UTF-8のみに対応。
	uint32_t GetStringLengthByte(const char* pCheckSrc);

	//unicode(UTF-16)文字の文字列バイト数を返却します。
	uint32_t GetStringLengthByte(const char16_t* pCheckSrc);

	//unicode(UTF-32)文字の文字列バイト数を返却します。
	//ただのループ。
	uint32_t GetStringLengthByte(const int32_t* pCheckSrc);

	//文字列のタイプをチェックし、その文字列で使用されている文字数を返却します。
	//文字列のタイプチェックは可能性の範囲のチェックとなります。
	//SJIS, UTF-8のみに対応。
	uint32_t GetStringCount(const char* pCheckSrc);

	//SJIS, UTF-8のみに対応。
	//第２引数に指定したタイプで強制的にカウントを行います。(SJIS混じりUTF8の対処)
	uint32_t GetStringCount(const char* pCheckSrc, SonikLibConvertType CountStrType);

	//unicode(UTF-16)文字の文字数を返却します。
	uint32_t GetStringCount(const char16_t* pCheckSrc);

	//unicode(UTF-32)文字の文字数を返却します。
	uint32_t GetStringCount(const int32_t* pCheckSrc);

	//UTF-8をUNICODE(UTF-32)に変換します。
	bool ConvertUTF8ToUTF32(char* pSrc, int32_t* pDest, uint32_t* DestBufferSize);

	//UNICODE(UTF-32)をUTF-8に変換します。
	bool ConvertUTF32ToUTF8(int32_t* pSrc, char* pDest, uint32_t* DestBufferSize);

	//UNICODE(UTF-32)をUNICODE(UTF-16)に変換します。
	bool ConvertUTF32ToUTF16(int32_t* pSrc, char16_t* pDest, uint32_t* DestBufferSize);

	//UNICODE(UTF16)をUNICODE(UTF-32)に変換します。
	bool ConvertUTF16ToUTF32(char16_t* pSrc, int32_t* pDest, uint32_t* DestBufferSize);

	//UTF8をUNICODE(UTF-16)に変換します。
	bool ConvertUTF8ToUTF16(char* pSrc, char16_t* pDest, uint32_t* DestBufferSize);

	//UNICODE(UTF-16)をUTF8に変換します。
	bool ConvertUTF16ToUTF8(char16_t* pSrc, char* pDest, uint32_t* DestBufferSize);


	//マルチバイト文字列をUTF8文字列に変換します。
	//第１引数の文字列は、可能性の判定として、SJIS判定であれば処理を行います。
	//第１引数の文字列に対して、Null終端がない場合の動作は、strlenと同様にバッファオーバーランを起こします。
	bool ConvertMBSToUTF8(char* pSrc, char* pDest, uint32_t* DestBufferSize);

	//UTF8文字列をマルチバイト文字列に変換します。
	//第１引数の文字列は、可能性の判定として、UTF8判定であれば処理を行います。
	//第１引数の文字列に対して、Null終端がない場合の動作は、strlenと同様にバッファオーバーランを起こします。
	bool ConvertUTF8ToMBS(char* pSrc, char* pDest, uint32_t* DestBufferSize);

	//マルチバイト文字列をUTF16文字列に変換します。
	//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
	bool ConvertMBStoUTF16(char* pSrc, char16_t* pDest, uint32_t* DestBufferSize);

	//UTF16文字列をマルチバイト文字列に変換します。
	//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
	bool ConvertUTF16toMBS(char16_t* pSrc, char* pDest, uint32_t* DestBufferSize);

	//UTF8文字列における、全角英数字及び、感嘆符(！(エクスクラメーションマーク))等の記号を半角英数字に変換します。
	//UTF-8における全角から半角変換において、領域オーバーをすることがないはずなのでそのまま領域を変換し、終端コードを最後に付与します。
	//第３引数は終端コードを含めた配列の使用要素数です。
	//FWC = Full Width Charcter
	//HWC = Half Width Charcter
	//AN = Alphabet and Number
	bool ConvertUTF8FWCToHWCForAN(const char* ConvertStr, char* dst, uint32_t& UsedSize);

	//UTF8文字列のおける、全角カナを半角カナに変換します。
	bool ConvertUTF8FWCToHWCForKANA(const char* ConvertStr, char* dst, uint32_t& UsedSize);

#elif defined(__SONIK_x86_64__)
//64bit definition
	//文字列のタイプが、SJISかUTF-8かを判別します。
	//完全な判別は不可能（らしい）なので可能性の範囲でチェックされた結果を返却します。
	//ASCIIはSJISとして結果を返却します。
	//UTF-16 は返却値としては返りません。
	SonikLibConvertType CheckConvertType(const char* pCheckSrc);

	//文字列のタイプをチェックし、その文字列で使用されているバイト数を返却します。
	//文字列のタイプチェックは可能性の範囲のチェックとなります。
	//SJIS, UTF-8のみに対応。
	uint64_t GetStringLengthByte(const char* pCheckSrc);

	//unicode(UTF-16)文字の文字列バイト数を返却します。
	uint64_t GetStringLengthByte(const char16_t* pCheckSrc);

	//unicode(UTF-32)文字の文字列バイト数を返却します。
	//ただのループ。
	uint64_t GetStringLengthByte(const int32_t* pCheckSrc);

	//文字列のタイプをチェックし、その文字列で使用されている文字数を返却します。
	//文字列のタイプチェックは可能性の範囲のチェックとなります。
	//SJIS, UTF-8のみに対応。
	uint64_t GetStringCount(const char* pCheckSrc);

	//SJIS, UTF-8のみに対応。
	//第２引数に指定したタイプで強制的にカウントを行います。(SJIS混じりUTF8の対処)
	uint64_t GetStringCount(const char* pCheckSrc, SonikLibConvertType CountStrType);

	//unicode(UTF-16)文字の文字数を返却します。
	uint64_t GetStringCount(const char16_t* pCheckSrc);

	//unicode(UTF-32)文字の文字数を返却します。
	uint64_t GetStringCount(const int32_t* pCheckSrc);

	//UTF-8をUNICODE(UTF-32)に変換します。
	bool ConvertUTF8ToUTF32(char* pSrc, int32_t* pDest, uint64_t* DestBufferSize);

	//UNICODE(UTF-32)をUTF-8に変換します。
	bool ConvertUTF32ToUTF8(int32_t* pSrc, char* pDest, uint64_t* DestBufferSize);

	//UNICODE(UTF-32)をUNICODE(UTF-16)に変換します。
	bool ConvertUTF32ToUTF16(int32_t* pSrc, char16_t* pDest, uint64_t* DestBufferSize);

	//UNICODE(UTF16)をUNICODE(UTF-32)に変換します。
	bool ConvertUTF16ToUTF32(char16_t* pSrc, int32_t* pDest, uint64_t* DestBufferSize);

	//UTF8をUNICODE(UTF-16)に変換します。
	bool ConvertUTF8ToUTF16(char* pSrc, char16_t* pDest, uint64_t* DestBufferSize);

	//UNICODE(UTF-16)をUTF8に変換します。
	bool ConvertUTF16ToUTF8(char16_t* pSrc, char* pDest, uint64_t* DestBufferSize);


	//マルチバイト文字列をUTF8文字列に変換します。
	//第１引数の文字列は、可能性の判定として、SJIS判定であれば処理を行います。
	//第１引数の文字列に対して、Null終端がない場合の動作は、strlenと同様にバッファオーバーランを起こします。
	bool ConvertMBSToUTF8(char* pSrc, char* pDest, uint64_t* DestBufferSize);

	//UTF8文字列をマルチバイト文字列に変換します。
	//第１引数の文字列は、可能性の判定として、UTF8判定であれば処理を行います。
	//第１引数の文字列に対して、Null終端がない場合の動作は、strlenと同様にバッファオーバーランを起こします。
	bool ConvertUTF8ToMBS(char* pSrc, char* pDest, uint64_t* DestBufferSize);

	//マルチバイト文字列をUTF16文字列に変換します。
	//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
	bool ConvertMBStoUTF16(char* pSrc, char16_t* pDest, uint64_t* DestBufferSize);

	//UTF16文字列をマルチバイト文字列に変換します。
	//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
	bool ConvertUTF16toMBS(char16_t* pSrc, char* pDest, uint64_t* DestBufferSize);

	//UTF8文字列における、全角英数字及び、感嘆符(！(エクスクラメーションマーク))等の記号を半角英数字に変換します。
	//UTF-8における全角から半角変換において、領域オーバーをすることがないはずなのでそのまま領域を変換し、終端コードを最後に付与します。
	//第３引数は終端コードを含めた配列の使用要素数です。
	//FWC = Full Width Charcter
	//HWC = Half Width Charcter
	//AN = Alphabet and Number
	bool ConvertUTF8FWCToHWCForAN(const char* ConvertStr, char* dst, uint64_t& UsedSize);

	//UTF8文字列のおける、全角カナを半角カナに変換します。
	bool ConvertUTF8FWCToHWCForKANA(const char* ConvertStr, char* dst, uint64_t& UsedSize);

#endif

};

namespace SonikLibStringControl
{
#ifdef __SONIK_I686__
	//c:指定された位置から指定された文字数を削除します。
	bool StringPointEraser(char* ControlStr, uint32_t StartPoint, uint32_t EndPoint, uint32_t MaxStrCnt);

#elif __SONIK_x86_64__
	//c:指定された位置から指定された文字数を削除します。
	bool StringPointEraser(char* ControlStr, uint64_t StartPoint, uint64_t EndPoint, uint64_t MaxStrCnt);

#endif

};


#endif /* SONIKString_SONIKStringCSonikERT_H_ */
