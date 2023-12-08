/*
 * SonikAudio_Implement.h
 *
 *  Created on: 2023/05/23
 *      Author: owner
 */

#ifndef INTERFACE_SONIKAUDIO_IMPLEMENT_H_
#define INTERFACE_SONIKAUDIO_IMPLEMENT_H_
//SonikAudioInterface のメイン実装

#include <stdlib.h>
#include <map>
#include "SonikAudio.h"
#include "../../Functions/LoadFunction.h"
#include "../../Format/SonikAudioFormat.h"
#include "../../../DllAccess/SonikDllAccessManager.h"
#include "../SAudioAccesserTypedef.h"
#include "../../AudioLoadTypedef.h"

//各プラットフォームのインターフェースクラスポインタを使うため前方宣言
namespace SonikAudioPlatForm
{
	class SonikPlatformAudioInterface;
};

namespace SonikAudioData
{
	class SonikAudioControlData;
};

namespace SonikAudioPlayerTask
{
	class SonikAudioPlayerTaskManager;
};

namespace SonikAudio
{
	class SonikAudioMixer;
};

//本体定義
namespace SonikAudio
{
	class SonikAudio_Implement : public SonikAudio::SonikAudioInterface
	{
	private:
		//Platformハンドル。
		SonikLib::SDllHandle m_platformHandle;

		//SamlingRateタイプ
		SonikAudio::SCVType SamlingType;
		std::map<uint32_t, SonikAudio::SAudioFormat> audiomap;

		//プレイヤーのオーディオデータを保持するmap
		std::map<uint64_t, SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioData::SonikAudioControlData>> ap_Data;

		//プレイヤーとミキサの仲介を担うタスクマネージャー
		SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioPlayerTask::SonikAudioPlayerTaskManager> m_TaskMng;

		//ミキサ
		SonikAudio::SonikAudioMixer* mp_Mixer;

	public:
		//constructor
		SonikAudio_Implement(void);
		//Destructor
		~SonikAudio_Implement(void);

		//イニシャライザ
		bool Initialize(uint32_t Set_Sampletype, SonikAudioPlatForm::SonikPlatformAudioInterface* Set_PFI_Pointer, SonikLib::SDllHandle SetHandle);

		//ピュア関数の実装
		//オーディオファイルをロードしてAudioPlayerを作成できるようにセットします。
		bool LoadAudio(const char* AudioFilePath, uint32_t SetAudioID);
		//オーディオプレイヤー(コントローラ)作成
		bool CreateAudioPlayer(uint32_t AudioID, SonikAudio::SAudioPlayer& GetPlayer);
		//ハードウェア情報を取得します。
		bool GetAudioHardwareInfo(void);
	};
};


#endif /* INTERFACE_SONIKAUDIO_IMPLEMENT_H_ */
