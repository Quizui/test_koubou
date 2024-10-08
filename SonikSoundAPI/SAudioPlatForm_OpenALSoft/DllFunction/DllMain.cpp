/*
 * DllMain.cpp
 *
 *  Created on: 2019/01/19
 *      Author: SONIC
 */

#include <windows.h>

#include "./Audio/PlatformInterface/PlatformAudioInterface.h"
#include "./SonikCAS/SonikAtomicLock.h"
#include "SonikAudioDllEntrance.h"
#include "../OpenALSource/open_al_interface.h"

AudioPlatformInterface::OpenALInterface* DLL_GLOBALPOINTER_SEVEADDRESS = nullptr;

//Dll EntryPoint
BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason) {

	case DLL_PROCESS_ATTACH: // DLLがプロセスのアドレス空間にマッピングされた。

		break;

	case DLL_THREAD_ATTACH: // スレッドが作成されようとしている。
		break;

	case DLL_THREAD_DETACH: // スレッドが破棄されようとしている。
		break;

	case DLL_PROCESS_DETACH: // DLLのマッピングが解除されようとしている。
//		if( DLL_GLOBALPOINTER_SEVEADDRESS != nullptr )
//		{
//			delete DLL_GLOBALPOINTER_SEVEADDRESS;
//		};

		break;

	}

	return TRUE;
}


bool PlatFormInitialize(char* DllPath, uint32_t SetBit, uint32_t SetSampling, uint32_t SetCh, SonikAudioPlatForm::SonikPlatformAudioInterface*& _GetAudioInterface_)
{
	static SonikLib::S_CAS::SonikAtomicLock lock_;

	lock_.lock();

	if( DLL_GLOBALPOINTER_SEVEADDRESS == nullptr )
	{
		//インスタンスがなければ作成。
		DLL_GLOBALPOINTER_SEVEADDRESS = new(std::nothrow) AudioPlatformInterface::OpenALInterface;
		if( DLL_GLOBALPOINTER_SEVEADDRESS == nullptr || DLL_GLOBALPOINTER_SEVEADDRESS == 0 )
		{
			DLL_GLOBALPOINTER_SEVEADDRESS = nullptr;
			lock_.unlock();
			return false;
		};


		if( !DLL_GLOBALPOINTER_SEVEADDRESS->InterfaceInitialize(DllPath, SetBit, SetSampling, SetCh) )
		{
			delete DLL_GLOBALPOINTER_SEVEADDRESS;
			DLL_GLOBALPOINTER_SEVEADDRESS = nullptr;

			lock_.unlock();
			return false;
		};

	};

	lock_.unlock();

	_GetAudioInterface_ = DLL_GLOBALPOINTER_SEVEADDRESS;
	return true;
};

void PlatFormDelete(void)
{
	if( DLL_GLOBALPOINTER_SEVEADDRESS != nullptr )
	{
		delete DLL_GLOBALPOINTER_SEVEADDRESS;
		DLL_GLOBALPOINTER_SEVEADDRESS = nullptr;
	};

};




