/*
 * SonikAudioListener.h
 *
 *  Created on: 2023/12/24
 *      Author: SONIC
 */

#ifndef LISTENER_SONIKAUDIOLISTENER_H_
#define LISTENER_SONIKAUDIOLISTENER_H_

namespace SonikAudio
{
	//オーディオリスナーさん
	//現状リスナーとプレイヤーの距離のためのものなので位置情報のみ。
	//音響などはまだまだ先だよねぇ。
	class SonikAudioListener
	{
	private:
		double PosX, PosY, PosZ;
		double* p_PosX, p_PosY, p_PosZ;

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
		double GetPositionX(void);
		const double* GetPositionX(void);
		const double& GetPositionX(void);
		double GetPositionY(void);
		const double* GetPositionY(void);
		const double& GetPositionY(void);
		double GetPositionZ(void);
		const double* GetPositionZ(void);
		const double& GetPositionZ(void);

	};


};



#endif /* LISTENER_SONIKAUDIOLISTENER_H_ */
