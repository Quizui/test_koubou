/*
 * SonikMathDistance.h
 *
 *  Created on: 2015/08/17
 *      Author: SONIK
 */

#ifndef SONIKMATHDISTANCE_H_
#define SONIKMATHDISTANCE_H_

//前方宣言====================================
namespace SonikMathDataBox
{
	class Sonik3DPoint;
};
namespace SonikMath
{
	//引数1のポイントをベースに引数2の座標との距離を算出します。
	double Distance(const SonikMathDataBox::Sonik3DPoint&, const SonikMathDataBox::Sonik3DPoint&);
	double Distance(const double , const double , const double, const double, const double, const double);

	//Distanceと方向値として設定されている3DPointからPanningを割り出します。
	double Panning(const double, const SonikMathDataBox::Sonik3DPoint&);
	double Panning(const double, const double, const double, const double);
};

namespace SonikMathDataBox
{
	class Sonik3DPoint
	{
		//friend
		friend double Distance(const SonikMathDataBox::Sonik3DPoint&, const SonikMathDataBox::Sonik3DPoint&);
		friend double Distance(const double , const double , const double, const double, const double, const double);

		friend double Panning(const double, const SonikMathDataBox::Sonik3DPoint&);
		friend double Panning(const double, const double, const double, const double);

		protected:
			double m_x, m_y, m_z;

		public:
			Sonik3DPoint(double _x_ = 0.0, double _y_ = 0.0, double _z_ =0.0);
			virtual ~Sonik3DPoint(void);

			void Set3Point(double _x_, double _y_, double _z_);
			void SetX(double _x_);
			void SetY(double _y_);
			void SetZ(double _z_);

			void Get3Point(double& _x_, double& _y_, double& _z_);
			void Get3Point(double* _x_, double* _y_, double* _z_);
			void Get3Point(double** _x_, double** _y_, double** _z_);
			double GetX(void);
			double* GetpX(void);
			void GetX(double& _x_);
			void GetX(double* _x_);
			double GetY(void);
			double* GetpY(void);
			void GetY(double& _y_);
			void GetY(double* _y_);
			double GetZ(void);
			double* GetpZ(void);
			void GetZ(double& _z_);
			void GetZ(double* _z_);
	};

	class SonikBazierBox
	{
		protected:
			double StartX, StartY; //始点
			double EndX, EndY;	  //終点
			double PivotX, PivotY; //制御点
			unsigned long Elapsed_Frame;  //始点から終点まで、何フレームで到達するか。

			double* m_saved_result_X;
			double* m_saved_result_Y;
		public:

			//引数最後のフラグは、先に計算を実施し、すべてのフレームの結果を保持しておくかどうかを設定します。(フレーム数 * doubleサイズ)分のメモリを使います。
			SonikBazierBox(double _x_ = 0.0, double _y_ = 0.0, double _endx_ = 0.0, double _endy_ = 0.0, double _pivx_ = 0.0, double  _pivy_ = 0.0, unsigned long _ef_= 0);
			~SonikBazierBox(void);

			//2次元のペジェ曲線に必要な情報を設定します。
			//引数最後のフラグは、先に計算を実施し、すべてのフレームの結果を保持しておくかどうかを設定します。(フレーム数 * doubleサイズ)分のメモリを使います。
			void SetValue(double _x_, double _y_, double _endx_, double _endy_, double _pivx_, double  _pivy_, unsigned long _ef_);

			//セットされた値からすべてのフレーム結果を算出し、保持します。
			bool SavedResultFrame(void);
			//保持しているフレーム結果をすべて破棄します。
			void SavedResultClear(void);

			//2次のベジェ曲線の位置点を算出します。
			//引数1: 結果であるX値を格納するために変数を指定します。
			//引数2: 結果であるY値を格納するために変数を指定します。
			//引数3: 始点から終点までの総合フレームの中で、何フレーム目の値を取得するのかを指定します。
			void Bezier_curveLine(double& GetX, double& GetY, unsigned long GetFrame);
	};


};

namespace SonikMath
{

//指定した3DPointのベクトルの長さを計算します。
inline double VectorLength(const SonikMathDataBox::Sonik3DPoint& _point_) noexcept;
//二点間の差を表すベクトルを取得します。
inline void diffVec(const SonikMathDataBox::Sonik3DPoint& _f_pos_, const SonikMathDataBox::Sonik3DPoint& _s_pos_, SonikMathDataBox::Sonik3DPoint& _outpoint_) noexcept;
//二点間のドット積を計算します。
inline double DotProductVec(const SonikMathDataBox::Sonik3DPoint& _f_pos_, const SonikMathDataBox::Sonik3DPoint& _s_pos_) noexcept;

//引数1のポイントをベースに引数2の座標との距離を算出します。
inline double Distance(const SonikMathDataBox::Sonik3DPoint& _f_point_, const SonikMathDataBox::Sonik3DPoint& _s_point_) noexcept;
inline double Distance(const double _fx_ = 0.0, const double _fy_ = 0.0, const double _fz_ = 0.0, const double _sx_ = 0.0, const double _sy_ = 0.0, const double _sz_ = 0.0) noexcept;

//位置を表す3DPointと方向を表す3DPointからパンニングを計算します。
//0.0~1.0の範囲で返却します。3DAudioにおいて、ステレオチャンネルなどでL側への計算に使う場合は(1.0 - 返却値)を掛けるようにしてください。
//3DPointのみの指定の場合は内部で全て計算するため、「使い回せる値もすべて計算しなおします。」でも指定が楽です。
//diff, veclenを指定する場合は、それぞれ、diffVec, VectorLengthで事前計算した値を指定することを想定しています。
//LisVec は リスナの方向ベクトルをVectorLengthで計算した結果を指定します。
//PlyVecは リスナーの位置ベクトルと、音源(Player）の位置ベクトルをdiffVecで計算した結果の値をVectorLengthで計算した結果を指定します。
inline double Panning(const SonikMathDataBox::Sonik3DPoint& _lispos_, const SonikMathDataBox::Sonik3DPoint& _plypos_, const SonikMathDataBox::Sonik3DPoint& _lisdir_, const SonikMathDataBox::Sonik3DPoint& _plydir_, const double _atten_max_ = 1.0, const double _attenuate_ = 0.3) noexcept;
inline double Panning(const double _dotproduct_, const double _lisdirveclen_, const double _diffveclen_, const double _dotproductdir_, const double _plydirveclen_, const double _atten_max_ = 1.0, const double _attenuate_ = 0.3) noexcept;
};



#endif /* SONIKMATHDISTANCE_H_ */
