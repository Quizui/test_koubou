/*
 * SonikFileController.h
 *
 *  Created on: 2018/11/16
 *      Author: SONIK
 */

#ifndef SONIKFILECONTROLLER_H_
#define SONIKFILECONTROLLER_H_

#include "stdio.h"
#include "stdlib.h"
#include <cstdint>

#include "../SonikCAS/SonikAtomicLock.h"
#include "../Container/SonikAtomicQueue.hpp"
#include "../SonikString/SonikString.h"

namespace SonikLibFileSystems
{
	enum class OpenMode : uint32_t
	{
		//UNKNOWN
		OPEN_UNKNOWN			= 0x00,
		//TEXT OPEN
		OPNE_TXT_READ			= 0x72,		//"r" 読み込み専用(Read Only) エラー + 新規作成不可
		OPEN_TXT_WRITE			= 0x77,		//"w" 書き込み専用(Write Only)	 内容を消去 + 新規作成可
		OPEN_TXT_WRITEADD		= 0x61,		//"a" 追加書き込み専用(AddWrite Only) 内容の最後に追記 + 新規作成可
		OPEN_TXT_READWRITE		= 0x2B72,	//"r+" 読み書き(Read And Write) エラー + 新規作成不可
		OPEN_TXT_WRITEREAD		= 0x2B77,	//"w+" 書き読み(Write And Read) 内容を消去 + 新規作成可
		OPEN_TXT_READADDWRITE	= 0x2B61,	//"a+" 読み込みと追加書き込み(Read And AddWrite) 内容の最後に追記 + 新規作成可
		//Binary OPEN
		OPNE_BIN_READ			= 0x6272,	//"rb" 読み込み専用(Read Only) エラー + 新規作成不可
		OPEN_BIN_WRITE			= 0x6277,	//"wb" 書き込み専用(Write Only)	 内容を消去 + 新規作成可
		OPEN_BIN_WRITEADD		= 0x6261,	//"ab" 追加書き込み専用(AddWrite Only) 内容の最後に追記 + 新規作成可
		OPEN_BIN_READWRITE		= 0x2B6272,	//"rb+" 読み書き(Read And Write) エラー + 新規作成不可
		OPEN_BIN_WRITEREAD		= 0x2B6277,	//"wb+" 書き読み(Write And Read) 内容を消去 + 新規作成可
		OPEN_BIN_READADDWRITE	= 0x2B6261	//"ab+" 読み込みと追加書き込み(Read And AddWrite) 内容の最後に追記 + 新規作成可

//		OPEN_INQUIRY	= 0x00,
//		OPEN_READ		= 0x01,
//		OPEN_WRITE		= 0x02,

	};

//	enum class ShareMode : unsigned long
//	{
//		SHARE_DEFAULT	= 0x00,
//		SHARE_DELETE	= 0x01,
//		SHARE_READ		= 0x02,
//		SHARE_WRITE		= 0x04
//	};

//	enum class CreateType : unsigned long
//	{
//		CT_NEW = 1,
//		CT_ALWAYS,
//		CTO_EXISTING,
//		CTO_ALWAYS,
//		CTT_EXISTING
//	};

};

namespace SonikLibFileSystemsControllers
{

#ifdef __SONIK_I686__
	class SonikFileStreamController
	{
	protected:
		FILE* m_pFile;
		uint32_t FileSize;
		SonikLibFileSystems::OpenMode m_opmode;

		SonikLib::SonikAtomicLock atmlock;
		bool Opend;

	public:
		//constructor
		SonikFileStreamController(void);
		//destructor
		virtual ~SonikFileStreamController(void);

		//FileOpen
		virtual bool OpenFile(const char* OpenFilePathStr, SonikLibFileSystems::OpenMode mode);
		//FileClose
		bool CloseFile(void);

		//読み込み位置を一番最初に移動します。
		void ReadSeekPointSet_Top(void);
		//読み込み位置を一番最後に移動します。
		void ReadSeekPointSet_End(void);
		//現在の読み込み位置を取得します。
		uint32_t ReadSeekPointGet(void);
		//現在の読み込み位置から指定文字数分或いは、指定サイズ分移動します。
		void ReadSeekPointSet_Point(uint32_t offset);

		//(バイナリモード専用)指定したサイズ分読み込みます。
		bool ReadBinary(int8_t* buffer, uint32_t size);

		//(テキストモード専用)指定した文字数分TEXTを読み込みます。
		virtual bool ReadText_CHR(int8_t* buffer, uint32_t ReadSize) =0;
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		virtual bool ReadText_Line(SonikLib::SonikString& LineStr, uint32_t GetRowCnt =1) =0;
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		virtual bool ReadText_LineQueue(SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint32_t GetRowCnt =1) =0;

	};

#elif defined(__SONIK_x86_64__)
	class SonikFileStreamController
	{
	protected:
		FILE* m_pFile;
		uint64_t FileSize;
		SonikLibFileSystems::OpenMode m_opmode;

		SonikLib::S_CAS::SonikAtomicLock atmlock;
		bool Opend;

	public:
		//constructor
		SonikFileStreamController(void);
		//destructor
		virtual ~SonikFileStreamController(void);

		//FileOpen
		virtual bool OpenFile(const char* OpenFilePathStr, SonikLibFileSystems::OpenMode mode);
		//FileClose
		bool CloseFile(void);

		//読み込み位置を一番最初に移動します。
		void ReadSeekPointSet_Top(void);
		//読み込み位置を一番最後に移動します。
		void ReadSeekPointSet_End(void);
		//現在の読み込み位置を取得します。
		uint64_t ReadSeekPointGet(void);
		//現在の読み込み位置から指定文字数分或いは、指定サイズ分移動します。
		void ReadSeekPointSet_Point(uint64_t offset);

		//(バイナリモード専用)指定したサイズ分読み込みます。
		bool ReadBinary(int8_t* buffer, uint64_t size);

		//(テキストモード専用)指定した文字数分TEXTを読み込みます。
		virtual bool ReadText_CHR(int8_t* buffer, uint64_t ReadSize) =0;
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		virtual bool ReadText_Line(SonikLib::SonikString& LineStr, uint64_t GetRowCnt =1) =0;
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		virtual bool ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint64_t GetRowCnt =1) =0;

	};
#endif

};

#endif /* SONIKFILECONTROLLER_H_ */
