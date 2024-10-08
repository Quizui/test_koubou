/*
 * SonikDllAccessManager.h
 *
 *  Created on: 2019/02/16
 *      Author: SONIK
 */

#ifndef SONIKDLLACCESSMANAGER_H_
#define SONIKDLLACCESSMANAGER_H_

#include <map>
#include <stdint.h>
#include "../SonikString/SonikString.h"
#include "../SmartPointer/SonikSmartPointer.hpp"
#include "../SonikCAS/SonikAtomicLock.h"

#if defined(__linux__)
typedef void* SONIK_DLL_ACCESS_MANAGER_POINTER;

#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>
using SONIK_DLL_ACCESS_MANAGER_POINTER = HINSTANCE__*;

#endif

namespace SonikDllOptions
{
	class SonikDllObject
	{
	public:
		//Constructor
		SonikDllObject(void)
		{
			//no process;
		};

		//Destructor
		virtual ~SonikDllObject(void)
		{
			//no process;
		};

		//pure functions
		virtual uintptr_t GetDllProcAddress(const char* ProcName)=0;
		virtual uintptr_t GetDllProcAddress(const char16_t* ProcName)=0;
		virtual uintptr_t GetDllProcAddress(const wchar_t* ProcName)=0;
	};

}; //end namespace SonikDllOptions

namespace SonikLib
{
	using SDllHandle = SonikLib::SharedSmtPtr<SonikDllOptions::SonikDllObject> ;

	class SonikDllHandleManager
	{
		typedef std::map<SonikLib::SonikString, SONIK_DLL_ACCESS_MANAGER_POINTER> maptype;
	private:
		SonikLib::S_CAS::SonikAtomicLock m_lock;
		maptype DllHandleList;

		//InnerClass宣言
		class DllObjectImple;

	private:
		//copy constructor
		SonikDllHandleManager(const SonikDllHandleManager& _copy_) = delete;
		SonikDllHandleManager(SonikDllHandleManager&& _move_) = delete;
		//override operator equal
		SonikDllHandleManager& operator =(const SonikDllHandleManager& _copy_) = delete;
		SonikDllHandleManager& operator =(SonikDllHandleManager&& _move_) = delete;

	public:
		//constructor
		SonikDllHandleManager(void);
		//Destructor
		~SonikDllHandleManager(void);

		bool DllGetLoad(const char* _DllPath_, SDllHandle& _GetDllObject);
		bool DllGetLoad(const char16_t* _DllPath_, SDllHandle& _GetDllObject);
		bool DllGetLoad(const wchar_t* _DllPath_, SDllHandle& _GetDllObject);

		bool DllLoad(const char* _DllPath_, const char* SetFind_DllName, const char* RegisterName);
		bool DllLoad(const char16_t* _DllPath_, const char16_t* SetFind_DllName, const char16_t* RegisterName);
		bool DllLoad(const wchar_t* _DllPath_, const wchar_t* SetFind_DllName, const wchar_t* RegisterName);

		void FreeDll(const char* FindDllName);
		void FreeDll(const char16_t* FindDllName);
		void FreeDll(const wchar_t* FindDllName);

		uintptr_t GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char* ProcName);
		uintptr_t GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char16_t* ProcName);
		uintptr_t GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const wchar_t* ProcName);

		SONIK_DLL_ACCESS_MANAGER_POINTER GetHandle(const char* FindDllName);
		SONIK_DLL_ACCESS_MANAGER_POINTER GetHandle(char16_t* FindDllName);
		SONIK_DLL_ACCESS_MANAGER_POINTER GetHandle(wchar_t* FindDllName);

	};

};



#endif /* SONIKDLLACCESSMANAGER_H_ */
