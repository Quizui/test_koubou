/*
 * open_al_interface.cpp
 *
 *  Created on: 2020/04/25
 *      Author: SONIC
 */

//#include <map>
//#include <iterator>
#include <algorithm>
#include <stdint.h>


#include "./open_al_interface.h"
#include "./Audio/AudioLoadTypedef.h"
//#include "./Audio/Functions/LoadFunction.h"
//#include "../OpenALFormat.h"
#include "./DllAccess/SonikDllAccessManager.h"



namespace AudioPlatformInterface
{
	//Constructor
	OpenALInterface::OpenALInterface(void)
	:m_aldev(nullptr)
	,m_alcontext(nullptr)
	,m_albuffers(nullptr)
	,m_albuffersCnt(2)
	,m_alsource(0)
	,SamlingType(SonikAudio::SCVType::B16_CH2_SR44100)
	,m_format(AL_FORMAT_STEREO16)
	,m_SamplingRate(0)
	,m_OneBufferDataSize(0)
	,m_dataBufferfunc(nullptr)
	,m_Queuefunc(nullptr)
	,m_UnQueuefunc(nullptr)
	,m_GetSource_i_func(nullptr)
	{

	};

	OpenALInterface::~OpenALInterface(void)
	{
		//SONIK_DLL_ACCESS_MANAGER_POINTER l_handle;

		//l_handle = SonikLib::SonikDllHandleManager::Instance().GetHandle("openal");
		if( !m_openal.IsNullptr() )
		{
			uintptr_t FuncPointer = 0;

			//再生のストップ
			//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alSourceStop");
			FuncPointer = m_openal->GetDllProcAddress("alSourceStop");
			(*reinterpret_cast<void(*)(ALuint)>(FuncPointer))(m_alsource);

			//ソースの破棄
			//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alDeleteSources");
			FuncPointer = m_openal->GetDllProcAddress("alDeleteSources");
			(*reinterpret_cast<void(*)(ALsizei, ALuint*)>(FuncPointer))(1, &m_alsource);

			//バッファーの破棄。
			//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alDeleteBuffers");
			FuncPointer = m_openal->GetDllProcAddress("alDeleteBuffers");
			(*reinterpret_cast<void(*)(ALsizei, ALuint*)>(FuncPointer))(m_albuffersCnt, m_albuffers);

			//もろもろ破棄。
			if( m_alcontext != nullptr )
			{
				//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alcDestroyContext");
				FuncPointer = m_openal->GetDllProcAddress("alcDestroyContext");
				(*reinterpret_cast<void(*)(ALCcontext*)>(FuncPointer))(m_alcontext);
			};

			if(m_aldev != nullptr)
			{
				//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alcCloseDevice");
				FuncPointer = m_openal->GetDllProcAddress("alcCloseDevice");
				(*reinterpret_cast<ALCboolean(*)(ALCdevice*)>(FuncPointer))(m_aldev);
			};

			if(m_albuffers != nullptr)
			{
				delete[] m_albuffers;
			};

		};


	};

	//イニシャライザ
	bool OpenALInterface::InterfaceInitialize(char* DllPath, uint32_t SetBit, uint32_t SetSampling, uint32_t SetCh)
	{
		unsigned long l_sampletype;

		if( SetSampling == 44100 )
		{
			SetSampling -= 100;
		};

		l_sampletype = SetBit;
		l_sampletype <<= 16;
		l_sampletype |= (SetCh << 8);
		l_sampletype |= static_cast<unsigned long>(SetSampling * 0.001);

		SamlingType = static_cast<SonikAudio::SCVType>(l_sampletype);
		m_SamplingRate = SetSampling;
		m_OneBufferDataSize = (SetBit * 0.125) * SetCh * SetSampling;

		//フォーマット変換(バッファへデータ格納するときに使うので...。
		switch((l_sampletype & 0xFFFF00) >> 8)
		{
		case 0x1001:
			m_format = AL_FORMAT_MONO16;
			break;

		case 0x1002:
			m_format = AL_FORMAT_STEREO16;
			break;

		default:
			m_format = AL_FORMAT_STEREO16;
		};

		SonikLib::SonikString _dllpath;

		//char dll_access_name[] = "openal";

		_dllpath = DllPath;
		_dllpath += "/soft_oal";

		SonikLib::SonikDllHandleManager l_dllmng;
		if( !l_dllmng.DllGetLoad(_dllpath.str_c(), m_openal) )
		{
			m_OneBufferDataSize = 0;
			m_SamplingRate = 0;
			m_format = 0;
			return false;
		};

		m_albuffers = new(std::nothrow) ALuint[m_albuffersCnt];
		if( m_albuffers == nullptr )
		{
			m_openal.ResetPointer(nullptr);
			m_OneBufferDataSize = 0;
			m_SamplingRate = 0;
			m_format = 0;
			return false;
		}

		//ハンドル取得まで確認できたので、とりあえずコンテキストの作成を行う。
		uintptr_t FuncPointer = 0;
		ALCenum err_;

		//エラー情報初期化
		//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alcGetError");
		FuncPointer = m_openal->GetDllProcAddress("alcGetError");
		(*reinterpret_cast<ALCenum(*)(ALCdevice*)>(FuncPointer))(NULL);

		//デバイスのオープン
		//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alcOpenDevice");
		FuncPointer = m_openal->GetDllProcAddress("alcOpenDevice");
		m_aldev = (*reinterpret_cast<ALCdevice* (*)(const ALCchar*)>(FuncPointer))(NULL); //デフォルト設定のデバイスをオープン

		//デバイスからコンテキストの取得
		//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alcCreateContext");
		FuncPointer = m_openal->GetDllProcAddress("alcCreateContext");
		m_alcontext = (*reinterpret_cast<ALCcontext* (*)(ALCdevice*, ALCint*)>(FuncPointer))(m_aldev, NULL);

		//カレントにコンテキストを設定
		//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alcMakeContextCurrent");
		FuncPointer = m_openal->GetDllProcAddress("alcMakeContextCurrent");
		(*reinterpret_cast<ALCboolean(*)(ALCcontext*)>(FuncPointer))(m_alcontext);

		//エラー情報初期化
		//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alcGetError");
		FuncPointer = m_openal->GetDllProcAddress("alcGetError");
		err_ = (*reinterpret_cast<ALCenum(*)(ALCdevice*)>(FuncPointer))(NULL);

		//バッファの作成(ダブルバッファで作っておく。)
		//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alGenBuffers");
		FuncPointer = m_openal->GetDllProcAddress("alGenBuffers");
		(*reinterpret_cast<void(*)(ALsizei,ALuint*)>(FuncPointer))(m_albuffersCnt, m_albuffers);
		//ソースの作成
		//FuncPointer = SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alGenSources");
		FuncPointer = m_openal->GetDllProcAddress("alGenSources");
		(*reinterpret_cast<void(*)(ALsizei,ALuint*)>(FuncPointer))(1, &m_alsource);
		//ソースのデフォルト設定
//		FuncPointer = m_openal->GetDllProcAddress("alSourcef");
//		(*reinterpret_cast<void(*)(ALuint,ALenum,ALfloat)>(FuncPointer))(m_source, AL_GAIN, 1.0f);
//		FuncPointer = m_openal->GetDllProcAddress("alSource3f");
//		(*reinterpret_cast<void(*)(ALuint,ALenum,ALfloat,ALfloat,ALfloat)>(FuncPointer))(m_source, AL_POSITION, 0.0f, 0.0f, 0.0f);



		//ストリーミング再生用のファンクション郡の取得。
		//FuncPointer			= SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alBufferData");
		FuncPointer			= m_openal->GetDllProcAddress("alBufferData");
		m_dataBufferfunc	= reinterpret_cast<void(*)(ALuint, ALenum, const ALvoid*, ALsizei, ALsizei)>(FuncPointer);

		//FuncPointer			= SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alSourceQueueBuffers");
		FuncPointer			= m_openal->GetDllProcAddress("alSourceQueueBuffers");
		m_Queuefunc			= reinterpret_cast<void(*)(ALuint, ALsizei, ALuint*)>(FuncPointer);

		//FuncPointer			= SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alSourceUnqueueBuffers");
		FuncPointer			= m_openal->GetDllProcAddress("alSourceUnqueueBuffers");
		m_UnQueuefunc		= reinterpret_cast<void(*)(ALuint, ALsizei, ALuint*)>(FuncPointer);

		//FuncPointer			= SonikLib::SonikDllHandleManager::Instance().GetDllProcAddress(l_handle, "alGetSourcei");
		FuncPointer			= m_openal->GetDllProcAddress("alGetSourcei");
		m_GetSource_i_func	= reinterpret_cast<void(*)(ALuint, ALenum, ALint*)>(FuncPointer);


		return true;
	};


	//オーディオのストリーミング再生を開始します。
	bool OpenALInterface::AudioBfferPlayngStart(void)
	{
		uint8_t* l_buffer = new(std::nothrow) uint8_t[m_OneBufferDataSize];
		if(l_buffer == nullptr)
		{
			return false;
		};

		std::fill_n(l_buffer, m_OneBufferDataSize, 0);

		for(uint32_t i = 0; i < m_albuffersCnt; ++i)
		{
			(*m_dataBufferfunc)(m_albuffers[i], m_format, l_buffer, m_OneBufferDataSize, m_SamplingRate);

		};

		(*m_Queuefunc)(m_alsource, m_albuffersCnt, m_albuffers);

		uintptr_t FuncPointer = m_openal->GetDllProcAddress("alSourcePlay");
		(*reinterpret_cast<void(*)(ALuint)>(FuncPointer))(m_alsource);

		return true;
	};

	//オーディオのストリーミングのバッファの空きバッファをセットされたバッファ情報で更新します。
	void OpenALInterface::BufferUpdate(int8_t* SetBuffer)
	{
		ALint l_processed = 0;
		ALuint l_buffer = 0;

		//空きバッファが取れるまでビジーループ
		while(l_processed == 0)
		{
			(*m_GetSource_i_func)(m_alsource, AL_BUFFERS_PROCESSED, &l_processed);
		};

		//使用可能バッファをキューから取得
		(*m_UnQueuefunc)(m_alsource, 1, &l_buffer);
		//バッファへデータコピー
		(*m_dataBufferfunc)(l_buffer, m_format, SetBuffer, m_OneBufferDataSize, m_SamplingRate);
		//再キュー
		(*m_Queuefunc)(m_alsource, 1, &l_buffer);

		//終わり
		return;


	};
};


