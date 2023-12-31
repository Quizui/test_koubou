/*
 * SonikAudioPlayer.h
 *
 *  Created on: 2023/07/16
 *      Author: owner
 */

#ifndef PLAYER_SONIKAUDIOPLAYER_H_
#define PLAYER_SONIKAUDIOPLAYER_H_

#include <stdint.h>
#include "../AudioSmartPointer.h"

//前方宣言
namespace SonikAudioDataInterface
{
	//プレイヤー側に渡す用のクラス。
	class SADInterface_PlayerSide;
};

namespace SonikAudioTaskInterface
{
	//プレイヤー側からマネージャへのアクセス用インタフェース。
	class SonikAudioPlayerTaskManagerInterface;
};

namespace SonikAudio
{
	//いわゆるオーディオコントローラーさん。
	class SonikAudioPlayer
	{
	private:
		SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> mp_AudioData;
		SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> mp_TskMng;

	public:
		//コンストラクタ
		SonikAudioPlayer(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetAudioData, SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng);
		//デストラクタ
		~SonikAudioPlayer(void);

		//音量のセットとゲット
		bool SetVolume(float SetValue);
		const float* GetVolume(void);

		//ポジションのセットとゲット
		bool SetPosition(float x, float y, float z);
		void GetPosition(float& x, float& y, float& z);

		//ポジションコネクトのセット
		//他のオブジェクトの座標と同期させたいときに使います。
		bool SetPositionConnect(float* x, float* y, float* z);

		//オーディオステータス関連
		bool Play(void);					//オーディステータスにPlayをセットします。
		bool Stop(void);					//オーディオステータスをStopにセットします。
		bool Suspend(void);				//オーディオステータスをSuspend(一時停止)に設定します。
		bool Repeat(bool RepeatState);	//再生終了後リピート再生するかを設定します。true=リピートします。 false=リピートせず停止します。
	};

}



#endif /* PLAYER_SONIKAUDIOPLAYER_H_ */
