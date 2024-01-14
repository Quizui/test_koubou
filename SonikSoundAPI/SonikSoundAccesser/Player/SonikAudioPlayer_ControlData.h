/*
 * SonikAudioPlayer_ControlData.h
 *
 *  Created on: 2023/10/16
 *      Author: owner
 */

#ifndef PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_H_
#define PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_H_

#include <stdint.h>
#include "../../../SonikCAS/SonikAtomicLock.h"
#include "SonikAudioPlayer_ControlData_Interface.h"
#include "../PlayStateEnums.h"
#include "../../AudioLoadTypedef.h"
#include "../SAudioAccesserTypedef.h"


namespace SonikAudioPoint
{
	class SonikAudio3DPoint;
};


namespace SonikAudioData
{

	//大本のクラス。
	class SonikAudioControlData : public SonikAudioDataInterface::SADInterface_PlayerSide
	{
	private:
		SonikAudio::SAudioFormat m_AudioData;			//オーディオデータへのスマートポインタ
		char* mp_ControlData;							//操作用ポインタ
		SonikAudioPoint::SonikAudio3DPoint* m_3dpos;	//3D座標ポジション
		float m_volume;									//オーディオの音量
		bool m_repeat;									//オーディオのリピートフラグ
		SonikAudioEnum::PlayStateID m_AudioState;		//オーディオのステータス(プレイ、ストップ等)
		uintptr_t m_uniqueid;							//メインインターフェースで管理される番号です。（自信のアドレス値をIDとして使います。)

		//CASLock
		SonikLib::S_CAS::SonikAtomicLock PositionLock[3];
		SonikLib::S_CAS::SonikAtomicLock AudioStateLock;
		SonikLib::S_CAS::SonikAtomicLock RepeatFlgLock;


	public:
		//コンストラクタ
		SonikAudioControlData(SonikAudio::SAudioFormat SetAudioPointer);
		//デストラクタ
		~SonikAudioControlData(void);
		//その他デフォルト(コピーコンストラクタ等)

		//コントロールオーディオのポインタを先頭ポインタへ移動します。
		void TopResetAudioControlPointer(void);

		//現在のコントロールポインタの位置が終端かどうかを確認します。
		bool Get_EndPointer(void);

		//コントロールオーディオポインタのゲット
		char** GetAudioControlPointer(void);

		//ポジションのセット
		void SetPositionX(double SetValue);
		void SetPositionY(double SetValue);
		void SetPositionZ(double SetValue);
		void SetPositionAll(double x, double y, double z);
		//別のポジションへのポインタとつなぎ、位置を一緒に動かしたいときに使います。
		//内部の個別ポジションに戻したい場合はnullptrを指定します。
		void SetPositonConnectX(double* x = nullptr);
		void SetPositonConnectY(double* y = nullptr);
		void SetPositonConnectZ(double* z = nullptr);
		void SetPositionConnectAll(double* x = nullptr, double* y = nullptr, double* z = nullptr);

		//音量(ボリューム)のセット
		void SetVolume(float SetValue);

		//繰り返し(リピート)フラグのセット
		void SetRepeat(bool SetValue);

		//オーディオステータスのセット
		void SetAudioState(SonikAudioEnum::PlayStateID SetValue);

		//継承元の純粋仮想関数の実装====================================
		//ポジションのゲット
		double GetPositionX(void);
		double GetPositionY(void);
		double GetPositionZ(void);
		void GetPositionAll(double& x, double& y, double& z);
		SonikAudioPoint::SonikAudio3DPoint& GetPositionAll(void);

		//音量(ボリューム)のゲット
		const float* GetVolume(void);

		//繰り返し(リピート)フラグのゲット
		bool GetRepeat(void);

		//Waveデータの全体サイズを取得します。
		uint32_t GetAllWaveDataSize(void);

		//ステータスのゲット
		SonikAudioEnum::PlayStateID GetPlayState(void);

		//Unique IDの取得(マップに登録する時や登録したものを検索するのに使います。
		uint64_t Get_UniqueID(void);

	};

};



#endif /* PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_H_ */
