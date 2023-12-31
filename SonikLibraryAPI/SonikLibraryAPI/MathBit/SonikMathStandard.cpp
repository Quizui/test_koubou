/*
 * SonikMathStandard.cpp
 *
 *  Created on: 2019/06/20
 *      Author: SONIC
 */

#include "SonikMathStandard.h"
#include "SonikMathTrigonometric.h"
#include "memory.h"
#include <stdint.h>

//#include <fftw3.h>

namespace SonikMath
{
	//2を底とする対数を計算します。
	int log2(int x)
	{
		int y;

		y = 0;
		while (x > 1)
		{
			x >>= 1;
			y++;
		}

		return y;
	};

	//指定した値の2の累乗(るいじょう)数を計算します。
	int pow2(int x)
	{
		int y;

		if (x == 0)
		{
			y = 1;
		}
		else
		{
			y = 2 << (x - 1);
		}

		return y;
	};

	//負の数の対応した平方根を計算します。
	double sqrt(double a)
	{
		double _E = 0.000001;

	    a = a < 0 ? -a : a;
	    double x = a / 2;
    	double e = x * x - a;
		double t = e < 0 ? -e : e;

	    while (1)
	    {
	    	if (t < _E)
	    	{
	    		return x;
	    	};

	    	x -= e / (x * 2);
	    };
	};


	//FFT(高速フーリエ変換)を行います。
	//作成途中。
	void FFT_1d(SonikComplex* p_complex, int TargetSampling)
	{
		//オイラーの公式
		//e^iθ = cosθ -i sinθ
		// i = -1の平方根(√-1)

		//

	};

	//IFFT(逆高速フーリエ変換を行います。
	//void IFFT_1d(SonikComplex* p_complex, int TargetSampling);
};


