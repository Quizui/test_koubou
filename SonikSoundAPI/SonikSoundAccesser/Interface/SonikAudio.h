/*
 * SonikAudio.h
 *
 *  Created on: 2023/05/17
 *      Author: owner
 */

#ifndef INTERFACE_SONIKAUDIO_H_
#define INTERFACE_SONIKAUDIO_H_

#include <stdint.h>
#include "../other/SAudioAccesserTypedef.h"

namespace SonikAudio
{
	//メインインターフェース
	class SonikAudioInterface
	{
	private:
		//none

	public:
		//コンストラクタ
		SonikAudioInterface()
		{
			//no_process;
		};
		//デストラクタ
		virtual ~SonikAudioInterface()
		{
			//no_process;
		};

		//純粋仮想関数
		//オーディオファイルロード
		virtual bool LoadAudio(const char* AudioFilePath, uint32_t SetAudioID) =0;
		//オーディオリスナの取得
		virtual void GetListener(SAudioListener& _out_get_) =0;
		//BGMとしてオーディオプレイヤーを作成します。
		virtual bool Create_BGM_AudioPlayer(uint32_t AudioID, SonikAudio::SAudioBGMPlayer& GetPlayer) =0;
		//SEとしてオーディオプレイヤーを作成します。
		virtual bool Create_SE_AudioPlayer(uint32_t AudioID, SonikAudio::SAudioSEPlayer& GetPlayer) =0;
		//ハードウェア情報を取得します。
		virtual bool GetAudioHardwareInfo(void) =0;

	};
};




#endif /* INTERFACE_SONIKAUDIO_H_ */
