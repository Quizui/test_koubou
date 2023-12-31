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


#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
typedef HINSTANCE__* SONIK_DLL_ACCESS_MANAGER_POINTER;
#elif defined(__linux__)
typedef void* SONIK_DLL_ACCESS_MANAGER_POINTER;
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

	};

	template <class PointerType>
	class SonikDllSmtPtr
	{
	private:
		PointerType* m_Pointer;

		unsigned long* m_Count;

	private:
		void AddRef(void)
		{
			++(*m_Count);
		};

		void Release(void)
		{
			--(*m_Count);

			if( (*m_Count) == 0 )
			{
				delete m_Pointer;
				delete m_Count;

			};

		};

	public:

		//constructor
		explicit SonikDllSmtPtr(PointerType* Pointer = nullptr)
		{
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = Pointer;

		};

		//コピーコンストラクタ
		SonikDllSmtPtr(const SonikDllSmtPtr<PointerType>& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			AddRef();

		};

		//Destructor
		~SonikDllSmtPtr(void)
		{
			Release();

		};

		SonikDllSmtPtr& operator =(const SonikDllSmtPtr<PointerType>& SmtPtr)
		{
			//自身への代入は意味が無いので行わない。
			if( SmtPtr.m_Pointer == m_Pointer )
			{
				return (*this);
			};

			Release();

			m_Count = SmtPtr.m_Count;
			m_Pointer = SmtPtr.m_Pointer;

			AddRef();

			return (*this);
		};

		bool operator ==(const SonikDllSmtPtr<PointerType>& SmtPtr)
		{
			if( m_Pointer == SmtPtr.m_Pointer )
			{
				return true;
			};

			return false;
		};

		bool operator ==(const unsigned long PtrVal)
		{
			if( m_Pointer == PtrVal )
			{
				return true;
			};

			return false;
		};

		void ResetPointer(PointerType* SetPointer = nullptr)
		{
			Release();

			//再初期化
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = SetPointer;
		};

		template <class Cast_Type>
		const Cast_Type* CastAccess(void)
		{
			return reinterpret_cast<Cast_Type*>(m_Pointer);
		};

		bool isPointerNull(void)
		{
			if(m_Pointer == nullptr)
			{
				return true;
			};

			return false;
		};

		PointerType* operator ->(void)
		{
			return m_Pointer;

		};
	};

};




namespace SonikLib
{
typedef SonikDllOptions::SonikDllSmtPtr<SonikDllOptions::SonikDllObject> SDllHandle;

#ifdef __SONIK_I686__


	class SonikDllHandleManager
	{
	private:
		std::map<std::string, SONIK_DLL_ACCESS_MANAGER_POINTER> DllHandleList;
		//		std::map<wchar_t*, SONIK_DLL_ACCESS_MANAGER_POINTER> DllHandleListW;

		class DllObjectImple;

	private:
		//constructor
		SonikDllHandleManager(void);

		//copy constructor
		SonikDllHandleManager(const SonikDllHandleManager& t_his);

		//override operator equal
		SonikDllHandleManager& operator =(const SonikDllHandleManager& t_his);

	public:
		//Destructor
		~SonikDllHandleManager(void);

		//Singleton Instance Access
		static SonikDllHandleManager& Instance(void);

		bool DllGetLoad(const char* _DllPath_, SDllHandle& _GetDllObject);
		bool DllGetLoad(const char16_t* _DllPath_, SDllHandle& _GetDllObject);

		bool DllLoad(const char* _DllPath_, const char* SetFind_DllName, const char* RegisterName);
		bool DllLoad(const char16_t* _DllPath_, const char16_t* SetFind_DllName, const char16_t* RegisterName);

		void FreeDll(const char* FindDllName);
		void FreeDll(const char16_t* FindDllName);

		uintptr_t GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char* ProcName);
		uintptr_t GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char16_t* ProcName);

		SONIK_DLL_ACCESS_MANAGER_POINTER GetHandle(const char* FindDllName);

		SONIK_DLL_ACCESS_MANAGER_POINTER GetHandle(char16_t* FindDllName);

	};



#elif defined(__SONIK_x86_64__)

	class SonikDllHandleManager
	{
		typedef std::map<SonikLib::SonikString, SONIK_DLL_ACCESS_MANAGER_POINTER> maptype;
	private:
		maptype DllHandleList;
//		std::map<wchar_t*, SONIK_DLL_ACCESS_MANAGER_POINTER> DllHandleListW;

		class DllObjectImple;

	private:
		//constructor
		SonikDllHandleManager(void);

		//copy constructor
		SonikDllHandleManager(const SonikDllHandleManager& t_his);

		//override operator equal
		SonikDllHandleManager& operator =(const SonikDllHandleManager& t_his);

	public:
		//Destructor
		~SonikDllHandleManager(void);

		//Singleton Instance Access
		static SonikDllHandleManager& Instance(void);

		bool DllGetLoad(const char* _DllPath_, SDllHandle& _GetDllObject);
		bool DllGetLoad(const char16_t* _DllPath_, SDllHandle& _GetDllObject);

		bool DllLoad(const char* _DllPath_, const char* SetFind_DllName, const char* RegisterName);
		bool DllLoad(const char16_t* _DllPath_, const char16_t* SetFind_DllName, const char16_t* RegisterName);

		void FreeDll(const char* FindDllName);
		void FreeDll(const char16_t* FindDllName);

		uintptr_t GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char* ProcName);
		uintptr_t GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char16_t* ProcName);

		SONIK_DLL_ACCESS_MANAGER_POINTER GetHandle(const char* FindDllName);

		SONIK_DLL_ACCESS_MANAGER_POINTER GetHandle(char16_t* FindDllName);

	};

#endif

};



#endif /* SONIKDLLACCESSMANAGER_H_ */
