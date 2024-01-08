/*
 * SonikAudioListener.h
 *
 *  Created on: 2023/12/24
 *      Author: SONIC
 */

#ifndef LISTENER_SONIKAUDIOLISTENER_H_
#define LISTENER_SONIKAUDIOLISTENER_H_

#include "../AudioPosition/SonikAudio3DPoint.h"

namespace SonikAudio
{
	//オーディオリスナーさん
	//現状リスナーとプレイヤーの距離のためのものなので位置情報のみ。
	//音響などはまだまだ先だよねぇ。
	class SonikAudioListener
	{
	private:
		SonikAudioPoint::SonikAudio3DPoint m_3dpos;	//3D座標ポジション

	public:
		//コンストラクタ
		SonikAudioListener(void);
		//デストラクタ
		~SonikAudioListener(void);

		//ポジションのセット
		void SetPosition(double x, double y, double z);
		void SetPositionX(double x);
		void SetPositionY(double y);
		void SetPositionZ(double z);

		//ポジションのゲット
		void GetPosition(double& x, double& y, double& z);
		void GetPosition(double*& x, double*& y, double*& z);
		SonikAudioPoint::SonikAudio3DPoint& GetPosition(void);
		double GetPositionX(void);
		void GetPositionX(const double* _out_);
		double GetPositionY(void);
		void GetPositionY(const double* _out_);
		double GetPositionZ(void);
		void GetPositionZ(const double* _out_);

	};


};



#endif /* LISTENER_SONIKAUDIOLISTENER_H_ */
