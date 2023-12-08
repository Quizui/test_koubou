/*
 * open_al_interface.h
 *
 *  Created on: 2020/04/25
 *      Author: SONIC
 */

#ifndef OPEN_AL_INTERFACE_H_
#define OPEN_AL_INTERFACE_H_

#include <map>
#include <vector>
#include <stdint.h>

#include "./PlatformInterface/PlatformAudioInterface.h"
#include "../AudioLoadTypedef.h"
#include "../Functions/LoadFunction.h"
#include "../../DllAccess/SonikDllAccessManager.h"

#include "../AL/al.h"
#include "../AL/alc.h"
#include "../AL/alext.h"
#include "../AL/efx.h"
#include "../AL/efx-creative.h"
#include "../AL/efx-presets.h"

namespace AudioPlatformInterface
{
	class OpenALInterface : public SonikAudioPlatForm::SonikPlatformAudioInterface
	{
	private:
		//OpenALSoftへのDLLハンドル
		SonikLib::SDllHandle m_openal;

		//必要なデバイスやコンテキスト
		ALCdevice* m_aldev;
		ALCcontext* m_alcontext;

		//OpenALバッファ
		ALuint* m_albuffers;
		//OpenALバッファカウント
		uint32_t m_albuffersCnt;
		//OpenALソース
		ALuint m_alsource;

		//SamlingRateタイプ
		SonikAudio::SCVType SamlingType;
		//ALFORMAT ストリーミング再生のときに必要。
		ALenum m_format;

		//ストリーミング再生に必要な再生用関数(一回一回取得するのめんどくさいので。)
		void(*m_dataBufferfunc)(ALuint, ALenum, const ALvoid*, ALsizei, ALsizei);
		void(*m_Queuefunc)(ALuint, ALsizei, ALuint*);
		void(*m_UnQueuefunc)(ALuint, ALsizei, ALuint*);
		void(*m_GetSource_i_func)(ALuint, ALenum, ALint*);


	public:
		//Constructor
		OpenALInterface(void);
		~OpenALInterface(void);

		//イニシャライザ
		bool InterfaceInitialize(char* DllPath, uint32_t SetBit, uint32_t SetSampling, uint32_t SetCh, uint32_t buffercnt);
		//クリアOpenAL(デストラクタじゃ動かないので)
		bool ClearAL(void);

		//スレッド用関数
		void AudioPlayFunc(void);

		//Pure Virtual Function
		//オーディオの再生を行います。
		void PlayAudio(uint8_t*& SetBuffer, const uint64_t& OneBufferSize, const uint32_t& SamplingRate);

	};

}


#endif /* OPEN_AL_INTERFACE_H_ */
