/*
 * SonikAudio_Mixer.h
 *
 *  Created on: 2023/06/04
 *      Author: owner
 */

#ifndef TASKMANAGER_SONIKAUDIO_MIXER_H_
#define TASKMANAGER_SONIKAUDIO_MIXER_H_

//Audioファイルを加工するミキサーさんです。
#include <stdint.h>
#include "../../container/SonikPriorityList.hpp"
#include "../../SmartPointer/SonikSmartPointer.hpp"
#include "../../SonikWorkThread/SonikWorkThreadEx.h"

namespace SonikAudioData
{
	class SonikAudioControlData;
};

namespace SonikAudio
{
	class SonikAudioListener;
    class SonikAudioEffecter;
};

namespace SonikAudioPlatForm
{
	class SonikPlatformAudioInterface;
};

namespace SonikAudio
{
	class SonikAudioMixer
	{
	private:
		//ミキサで逐次処理していくオーディオのリスト。
		SonikLib::SonikPriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>* mp_AudioList;
		//処理用スレッド
		SonikLib::WorkThreadEx* mp_thread;

		//プラットフォーム別の送出先
		//プラットフォームインタフェースはDLLアンタッチ時に自動的に破棄されるので何もしない。
		//※アンタッチ時に殺そうとするとDll先で処理が戻らなくなるのでデストラクタで廃棄関数を呼ぶ。
		//この変数の破棄については本クラスではノンタッチ
		SonikAudioPlatForm::SonikPlatformAudioInterface* mp_platform;

		//リスナ
		SonikLib::SharedSmtPtr<SonikAudio::SonikAudioListener> mp_Listener;

		//送出用バッファ
		int8_t* mp_buffer;
		//１サンプリングあたりの総合バイト数
		//例：16bit 2ch 44100 -> bit * ch * Sampling = 16 * 2 * 44100 = 総合バイト数。
		uint64_t OneSamplingByteSize;
		//サンプリングレート
		unsigned long m_samplingRate;

        //エフェクタオブジェクト
        SonikAudio::SonikAudioEffecter* mp_effecter;

		//関数ポインタ
		void (SonikAudioMixer::*p_mfunc_)(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr);

	private:
		//スレッドで駆動させる関数。
		void MixerThreadFunc(void);

		//各チャンネル数で処理が微妙に異なるので....。
		//それぞれ作るのちょーめんどくさいけどループ内の配列をチャンネル数で展開できるので処理が気持ち重くならないかも。
		void Mixing_16bit_1ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr);
		void Mixing_16bit_2ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr);
		void Mixing_16bit_4ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr);
		void Mixing_16bit_6ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr); // 5.1ch (低音専用が0.1chあるが1chとしてカウントされるため。
		void Mixing_16bit_8ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr); // 7.1ch (低音専用が0.1chあるが1chとしてカウントされるため。

		void Mixing_32bit_1ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr);
		void Mixing_32bit_2ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr);
		void Mixing_32bit_4ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr);
		void Mixing_32bit_6ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr); // 5.1ch (低音専用が0.1chあるが1chとしてカウントされるため。
		void Mixing_32bit_8ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr); // 7.1ch (低音専用が0.1chあるが1chとしてカウントされるため。

	public:
		//コンストラクタ
		SonikAudioMixer(void);
		//デストラクタ
		~SonikAudioMixer(void);

		//イニシャライザ
		bool Initialize(uint32_t SetAudioListMax, uint32_t FormatBit, uint16_t SetChannel, uint32_t SetSamplingRate, SonikAudioPlatForm::SonikPlatformAudioInterface* Set_PFI_Pointer, SonikLib::SharedSmtPtr<SonikAudio::SonikAudioListener> SetListener);

		//オーディオの追加。
		bool AddAudio(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> SetAudio);

	};


};



#endif /* TASKMANAGER_SONIKAUDIO_MIXER_H_ */
