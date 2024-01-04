/*
 * SonikNormalize.h
 *
 *  Created on: 2019/01/20
 *      Author: SONIC
 */

#ifndef MATHBIT_SONIKNORMALIZE_H_
#define MATHBIT_SONIKNORMALIZE_H_


namespace SonikMath
{

	//0.0 ~ 1.0へ正規化します。
	//引数1：正規化1.0 として扱いたい値
	inline float Normalize(const float& MaxValue, const float& NowValue);

	//0.0 ~ 1.0へ正規化します。
	//最大値を0.0
	//最小値を1.0
	//として扱います。
	inline float NormalizeInverse(const float& MaxValue, const float& NowValue);

	//引数１の値を 引数4 ~ 引数5 の範囲に正規化します。
	// Y = ( (X - Xmin) / (Xmax - Xmin) ) * (Max - Min) + Min
	inline float Normalize_Max_to_MinF(long NTV, long NTV_Max, long NTV_Min, long NormalizeMax, long NormalizeMin);
	//double版
	inline double Normalize_Max_to_Min(long long NTV, long long NTV_Max, long long NTV_Min, long long NormalizeMax, long long NormalizeMin);

};


#endif /* MATHBIT_SONIKNORMALIZE_H_ */
