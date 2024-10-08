/*
 * SonikFileSystems.h
 *
 *  Created on: 2018/11/14
 *      Author: SONIK
 */

#ifndef SONIKFILESYSTEMS_H_
#define SONIKFILESYSTEMS_H_

#include "../SmartPointer/SonikSmartPointer.hpp"
#include "../SonikString/SonikString.h"

#include <stdint.h>

//前方宣言
namespace SonikLib
{
	namespace Container
	{
		template<class QueueType>
		class SonikAtomicQueue;
	};
};

namespace SonikLib
{

	namespace FileSystemGlobal
	{
		//指定したフォルダにあるファイル数を取得します。(サブディレクトリ及び、サブディレクトリ内のファイルはカウントに含まれません。
		uint64_t GetDirectoryInFileCount(SonikLib::SonikString  _directoryPath_);

		//指定したフォルダにあるファイル名を列挙します。
		bool GetDirectoryInFileNameEnumeration(SonikLib::SonikString  _directoryPath_, SonikLib::Container::SonikAtomicQueue<SonikLib::SonikString>& retEnums);

	};
};



#endif /* SONIKFILESYSTEMS_H_ */
