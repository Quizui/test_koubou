/*
 * SonikDllAccessManager_x64.cpp
 *
 *  Created on: 2019/02/16
 *      Author: SONIK
 */

#ifdef __SONIK_x86_64__

#include <map>

#include "SonikDllAccessManager.h"
#include "SonikDllLoader.h"
#include "../SonikCAS/SonikAtomicLock.h"


namespace SonikDllAccessManagerGlobalVariable
{
    SonikLib::S_CAS::SonikAtomicLock DllAccessInstanceBlocked;
};

namespace SonikLib
{

#if defined(_WIN32) || defined(_WIN64)

	//ClassImplement
	class SonikDllHandleManager::DllObjectImple : public SonikDllOptions::SonikDllObject
	{
	private:
		SONIK_DLL_ACCESS_MANAGER_POINTER m_handle;

	public:
		//Constructor
		DllObjectImple(SONIK_DLL_ACCESS_MANAGER_POINTER SetHandle)
		:m_handle(SetHandle)
		 {
			//no process
		 };

		//Destructor
		~DllObjectImple(void)
		{
			if( m_handle != 0 )
			{
				SonikLibLoderFree(m_handle);
			};
		};

		//PureFunctions
		uintptr_t GetDllProcAddress(const char* ProcName)
		{
			SonikLib::SonikString str;
			str = ProcName;

			return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(m_handle, str.c_str()));
		};

		uintptr_t GetDllProcAddress(const char16_t* ProcName)
		{
			SonikLib::SonikString str;
			str = ProcName;

			return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(m_handle, str.c_str()));
		}

	};

	//constructor
	SonikDllHandleManager::SonikDllHandleManager(void)
	{
		//no process
	};

	//copy constructor
	SonikDllHandleManager::SonikDllHandleManager(const SonikDllHandleManager& t_his)
	{
		//no process
	};

	//override operator equal
	SonikDllHandleManager& SonikDllHandleManager::operator =(const SonikDllHandleManager& t_his)
	{
		return (*this);
	};

	//Destructor
	SonikDllHandleManager::~SonikDllHandleManager(void)
	{
		maptype::iterator _it = DllHandleList.begin();

		while( _it != DllHandleList.end() )
		{
			SonikLibLoderFree(_it->second);
			_it = DllHandleList.erase(_it);
		};

	};

	//Singleton Instance Access
	SonikDllHandleManager& SonikDllHandleManager::Instance(void)
	{
		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.lock();

		static SonikDllHandleManager inst_;

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();

		return inst_;
	};


	bool SonikDllHandleManager::DllGetLoad(const char* _DllPath_, SDllHandle& _GetDllObject)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString dll_str;

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.lock();

		dll_str = _DllPath_;

		handles_ = SonikLibLoder(dll_str.c_str(), LOAD_WITH_ALTERED_SEARCH_PATH);
		if(handles_ == 0)
		{
			SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
			return false;
		};

		DllObjectImple* l_imple = new(std::nothrow) DllObjectImple(handles_);
		if( l_imple == 0 )
		{
			return false;
		};

		_GetDllObject.ResetPointer(l_imple);

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
		return true;
	};

	bool SonikDllHandleManager::DllGetLoad(const char16_t* _DllPath_, SDllHandle& _GetDllObject)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString dll_str;

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.lock();

		dll_str = _DllPath_;

		handles_ = SonikLibLoder(dll_str.c_str(), LOAD_WITH_ALTERED_SEARCH_PATH);
		if(handles_ == 0)
		{
			SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
			return false;
		};

		DllObjectImple* l_imple = new(std::nothrow) DllObjectImple(handles_);
		if( l_imple == 0 )
		{
			return false;
		};

		_GetDllObject.ResetPointer(l_imple);

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
		return true;
	};

	bool SonikDllHandleManager::DllLoad(const char* _DllPath_, const char* SetFind_DllName, const char* RegisterName)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString findstr;
//		SonikLib::SonikString secondstr;

		findstr = RegisterName;
		if( DllHandleList.find(findstr.c_str()) != DllHandleList.end() )
		{
			return true;
		};

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.lock();

		findstr = _DllPath_;
//		findstr += "/";
//
//		secondstr = SetFind_DllName;
//		findstr += secondstr;

		handles_ = SonikLibLoder(findstr.c_str(), LOAD_WITH_ALTERED_SEARCH_PATH);
		if(handles_ == 0)
		{
			SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
			return false;
		};

		findstr = RegisterName;
		if( DllHandleList.insert( maptype::value_type(findstr, handles_) ).second )
		{
			SonikLibLoderFree(handles_);
			SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
			return false;
		};

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
		return true;

	};

	bool SonikDllHandleManager::DllLoad(const char16_t* _DllPath_, const char16_t* SetFind_DllName, const char16_t* RegisterName)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString findstr;
//		SonikLib::SonikString secondstr;

		findstr = RegisterName;
		if( DllHandleList.find(findstr.c_str()) != DllHandleList.end() )
		{
			return true;
		};

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.lock();

		findstr = _DllPath_;
//		findstr += "/";
//
//		secondstr = SetFind_DllName;
//		findstr += secondstr;

		handles_ = SonikLibLoder(_DllPath_, LOAD_WITH_ALTERED_SEARCH_PATH);
		if(handles_ == 0)
		{
			SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
			return false;
		};

		findstr = RegisterName;
		if( !DllHandleList.insert( maptype::value_type(findstr, handles_) ).second )
		{
			SonikLibLoderFree(handles_);
			SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
			return false;
		};

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
		return true;

	};

	void SonikDllHandleManager::FreeDll(const char* FindDllName)
	{
//		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.c_str());
		if( it == DllHandleList.end() )
		{
			return;
		};

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.lock();

		if( !SonikLibLoderFree(it->second) )
		{
			return;
		};

		DllHandleList.erase(it);

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
		return;

	};

	void SonikDllHandleManager::FreeDll(const char16_t* FindDllName)
	{
//		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.c_str());
		if( it == DllHandleList.end() )
		{
			return;
		};

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.lock();

		if( !SonikLibLoderFree(it->second) )
		{
			return;
		};

		DllHandleList.erase(it);

		SonikDllAccessManagerGlobalVariable::DllAccessInstanceBlocked.Unlock();
		return;

	};

	uintptr_t SonikDllHandleManager::GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char* ProcName)
	{
		SonikLib::SonikString str;
		str = ProcName;

		return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(dllhandle, str.c_str()));

	};

	uintptr_t SonikDllHandleManager::GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char16_t* ProcName)
	{
		SonikLib::SonikString str;
		str = ProcName;

		return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(dllhandle, str.c_str()));
	};


	SONIK_DLL_ACCESS_MANAGER_POINTER SonikDllHandleManager::GetHandle(const char* FindDllName)
	{
		maptype::iterator it;

		it = DllHandleList.find(FindDllName);
		if( it == DllHandleList.end() )
		{
			return 0;
		};

		return it->second;
	};

	SONIK_DLL_ACCESS_MANAGER_POINTER SonikDllHandleManager::GetHandle(char16_t* FindDllName)
	{
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.c_str());
		if( it == DllHandleList.end() )
		{
			return 0;
		};

		return it->second;
	};

#elif defined(__linux__)

#endif

};



#endif
