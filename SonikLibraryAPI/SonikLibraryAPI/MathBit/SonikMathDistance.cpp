/*
 * SonikMathDistance.cpp
 *
 *  Created on: 2015/08/17
 *      Author: SONIK
 */

#include "SonikMathDistance.h"
#include "SonikMathStandard.h"

#include <stdint.h>
#include <new>

namespace SonikMathDataBox
{
	//=====================================
	//					Sonik3DPoint Implement
	//=====================================
	Sonik3DPoint::Sonik3DPoint(double _x_, double _y_, double _z_)
	:m_x(_x_)
	,m_y(_y_)
	,m_z(_z_)
	{

	};

	Sonik3DPoint::~Sonik3DPoint(void)
	{

	};

	void Sonik3DPoint::Set3Point(double _x_, double _y_, double _z_)
	{
		m_x = _x_;
		m_y = _y_;
		m_z = _z_;
	};

	void Sonik3DPoint::SetX(double _x_)
	{
		m_x = _x_;
	};
	void Sonik3DPoint::SetY(double _y_)
	{
		m_y = _y_;
	};
	void Sonik3DPoint::SetZ(double _z_)
	{
		m_z = _z_;
	};

	void Sonik3DPoint::Get3Point(double& _x_, double& _y_, double& _z_)
	{
		_x_ = m_x;
		_y_ = m_y;
		_y_ = m_z;
	};

	void Sonik3DPoint::Get3Point(double* _x_, double* _y_, double* _z_)
	{
		if( _x_ == nullptr || _y_ == nullptr || _z_ == nullptr )
		{
			return;
		};

		(*_x_) = m_x;
		(*_y_) = m_y;
		(*_z_) = m_z;
	};

	void Sonik3DPoint::Get3Point(double** _x_, double** _y_, double** _z_)
	{
		(*_x_) = &m_x;
		(*_y_) = &m_y;
		(*_z_) = &m_z;
	};

	double Sonik3DPoint::GetX(void)
	{
		return m_x;
	};

	double* Sonik3DPoint::GetpX(void)
	{
		return &m_x;
	};

	void Sonik3DPoint::GetX(double& _x_)
	{
		_x_ = m_x;
	};

	void Sonik3DPoint::GetX(double* _x_)
	{
		if( _x_ == nullptr)
		{
			return;
		};

		(*_x_) = m_x;
	};

	double Sonik3DPoint::GetY(void)
	{
		return m_y;
	};

	double* Sonik3DPoint::GetpY(void)
	{
		return &m_y;
	};

	void Sonik3DPoint::GetY(double& _y_)
	{
		_y_ = m_y;

	};

	void Sonik3DPoint::GetY(double* _y_)
	{
		if(_y_ == nullptr)
		{
			return;
		};

		(*_y_) = m_y;
	};

	double Sonik3DPoint::GetZ(void)
	{
		return m_z;
	};

	double* Sonik3DPoint::GetpZ(void)
	{
		return &m_z;
	};

	void Sonik3DPoint::GetZ(double& _z_)
	{
		_z_ = m_z;
	};

	void Sonik3DPoint::GetZ(double* _z_)
	{
		if( _z_ == nullptr )
		{
			return;
		};

		(*_z_) = m_z;
	};

	//=====================================
	//					SonikBazierBox Implement
	//=====================================
	SonikBazierBox::SonikBazierBox(double _x_, double _y_, double _endx_, double _endy_, double _pivx_, double  _pivy_, unsigned long _ef_)
	:StartX(_x_)
	,StartY(_y_)
	,EndX(_endx_)
	,EndY(_endy_)
	,PivotX(_pivx_)
	,PivotY(_pivy_)
	,Elapsed_Frame(_ef_)
	,m_saved_result_X(nullptr)
	,m_saved_result_Y(nullptr)
	{

	};
	SonikBazierBox::~SonikBazierBox(void)
	{
		if( m_saved_result_X != nullptr )
		{
			delete[] m_saved_result_X;
		};

		if( m_saved_result_Y != nullptr )
		{
			delete[] m_saved_result_Y;
		};

	};

	//セットされた値からすべてのフレーム結果を算出し、保持します。
	bool SonikBazierBox::SavedResultFrame(void)
	{
		//すでに配列を持っていれば一回開放。
		if( m_saved_result_X != nullptr )
		{
			delete[] m_saved_result_X;
			m_saved_result_X = nullptr;
		};
		if( m_saved_result_Y != nullptr )
		{
			delete[] m_saved_result_Y;
			m_saved_result_Y = nullptr;
		};

		//配列作成。
		m_saved_result_X = new(std::nothrow) double[Elapsed_Frame];
		if( m_saved_result_X == nullptr )
		{
			return false;
		};

		m_saved_result_Y = new(std::nothrow) double[Elapsed_Frame];
		if( m_saved_result_X == nullptr )
		{
			delete[] m_saved_result_X;
			m_saved_result_X = nullptr;
			return false;
		};

		double _getx;
		double _gety;
		for(uint32_t i=0; i < Elapsed_Frame; ++i)
		{
			Bezier_curveLine(_getx, _gety, i);
			m_saved_result_X[i] = _getx;
			m_saved_result_Y[i] = _gety;
		};

		return true;
	};
	//保持しているフレーム結果をすべて破棄します。
	void SonikBazierBox::SavedResultClear(void)
	{
		//すでに配列を持っていれば一回開放。
		if( m_saved_result_X != nullptr )
		{
			delete[] m_saved_result_X;
			m_saved_result_X = nullptr;
		};
		if( m_saved_result_Y != nullptr )
		{
			delete[] m_saved_result_Y;
			m_saved_result_Y = nullptr;
		};
	};

	//2次元のペジェ曲線に必要な情報を設定します。
	//引数最後のフラグは、先に計算を実施し、すべてのフレームの結果を保持しておくかどうかを設定します。(フレーム数 * doubleサイズ)分のメモリを使います。
	void SonikBazierBox::SetValue(double _x_, double _y_, double _endx_, double _endy_, double _pivx_, double  _pivy_, unsigned long _ef_)
	{
		StartX = _x_;
		StartY = _y_;
		EndX = _endx_;
		EndY = _endy_;
		PivotX = _pivx_;
		PivotY = _pivy_;
		Elapsed_Frame = _ef_;
	};

	//2次のベジェ曲線の位置点を算出します。
	//引数1: 結果であるX値を格納するために変数を指定します。
	//引数2: 結果であるY値を格納するために変数を指定します。
	//引数3: 始点から終点までの総合フレームの中で、何フレーム目の値を取得するのかを指定します。
	void SonikBazierBox::Bezier_curveLine(double& GetX, double& GetY, unsigned long GetFrame)
	{
		double time = 0.0;

		if(Elapsed_Frame < GetFrame)
		{
			time = 1.0;
		}else
		{
			time = GetFrame * (1 * Elapsed_Frame);
		};

		GetX = ((1.0 - time) * (1.0 - time) * StartX) + (2 * (1.0 - time) * time * PivotX) + (time * time * EndX);
		GetY = ((1.0 - time) * (1.0 - time) * StartY) + (2 * (1.0 - time) * time * PivotY) + (time * time * EndY);
	};

};


namespace SonikMath
{
	//指定した3DPointのベクトルの長さを計算します。
	double VectorLength(const SonikMathDataBox::Sonik3DPoint& _point_)
	{
		return SonikMath::sqrt(_point_.m_x * _point_.m_x + _point_.m_y * _point_.m_y + _point_.m_z * _point_.m_z);
	};

	//二点間の差を表すベクトルを取得します。
	void diffVec(const SonikMathDataBox::Sonik3DPoint& _f_pos_, const SonikMathDataBox::Sonik3DPoint& _s_pos_, SonikMathDataBox::Sonik3DPoint& _outpoint_)
	{
	    _outpoint_.m_x = _s_pos_.m_x - _f_pos_.m_x;
	    _outpoint_.m_y = _s_pos_.m_y - _f_pos_.m_y;
	    _outpoint_.m_z = _s_pos_.m_z - _f_pos_.m_z;
	    return;
	};

	//二点間のドット積を計算します。
	double DotProductVec(const SonikMathDataBox::Sonik3DPoint& _f_pos_, const SonikMathDataBox::Sonik3DPoint& _s_pos_)
	{
		return _f_pos_.m_x * _s_pos_.m_x + _f_pos_.m_y * _s_pos_.m_y + _f_pos_.m_z * _s_pos_.m_z;
	};


	//本クラスと引数で指定されたオブジェクト或いは座標との距離を算出します。
	double Distance(const SonikMathDataBox::Sonik3DPoint& _f_point_, const SonikMathDataBox::Sonik3DPoint& _s_point_)
	{
		double _distance[3];

		_distance[0] = _f_point_.m_x - _s_point_.m_x;
		_distance[1] = _f_point_.m_y - _s_point_.m_y;
		_distance[2] = _f_point_.m_z - _s_point_.m_z;

		return SonikMath::sqrt( _distance[0] * _distance[0] + _distance[1] * _distance[1] + _distance[2] * _distance[2]);

	};

	double Distance(const double _fx_, const double _fy_, const double _fz_, const double _sx_, const double _sy_, const double _sz_)
	{

		double _distance[3];

		_distance[0] = _fx_ - _sx_;
		_distance[1] = _fy_ - _sy_;
		_distance[2] = _fz_ - _sz_;

		return SonikMath::sqrt( _distance[0] * _distance[0] + _distance[1] * _distance[1] + _distance[2] * _distance[2]);
	};

	//位置を表す3DPointと方向を表す3DPointからパンニングを計算します。
	//0.0~1.0の範囲で返却します。3DAudioにおいて、ステレオチャンネルなどでL側への計算に使う場合は(1.0 - 返却値)を掛けるようにしてください。
	//3DPointのみの指定の場合は内部で全て計算するため、「使い回せる値もすべて計算しなおします。」でも指定が楽です。
	//diff, veclenを指定する場合は、それぞれ、diffVec, VectorLengthで事前計算した値を指定することを想定しています。
	//LisVec は リスナの方向ベクトルをVectorLengthで計算した結果を指定します。
	//PlyVecは リスナーの位置ベクトルと、音源(Player）の位置ベクトルをdiffVecで計算した結果の値をVectorLengthで計算した結果を指定します。
	double Panning(const SonikMathDataBox::Sonik3DPoint& _lispos_, const SonikMathDataBox::Sonik3DPoint& _plypos_, const SonikMathDataBox::Sonik3DPoint& _lisdir_, const SonikMathDataBox::Sonik3DPoint& _plydir_, const double _atten_max_, const double _attenuate_)
	{
	    // リスナーから音源へのベクトルを計算
		SonikMathDataBox::Sonik3DPoint l_point;
		diffVec(_plypos_, _lispos_, l_point);

	    // リスナーの向きと音源のベクトルの内積を計算
	    double dotProduct = DotProductVec(_lisdir_, l_point);

	    // リスナーの向きと音源のベクトルの長さを計算
	    double listenerDirLength = VectorLength(_lisdir_);
	    double sourceVecLength = VectorLength(l_point);

	    // 長さの逆数を計算
	    double invListenerDirLength = 1.0 / listenerDirLength;
	    double invSourceVecLength = 1.0 / sourceVecLength;

	    // パンニング角度を計算（-1.0から1.0の範囲）
	    double panning = dotProduct * invListenerDirLength * invSourceVecLength;

	    // パンニングの値を0.0から1.0の範囲にマッピング
	    panning = (panning + 1.0) * 0.5;

	    // リスナーの向きと音源の向きの内積を計算
	    double dotProductDir = DotProductVec(_lisdir_, _plydir_);

	    // リスナーの向きと音源の向きの長さを計算
	    double sourceDirLength = VectorLength(_plydir_);

	    // 長さの逆数を計算
	    double invSourceDirLength = 1.0 / sourceDirLength;

	    // 音源の向きとリスナーの向きの間の角度を計算（-1.0から1.0の範囲）
	    double directionality = dotProductDir * invListenerDirLength * invSourceDirLength;

	    // 音の強さを調整
	    double adjustedVolume = _attenuate_ + (_atten_max_ - _attenuate_) * ((directionality + 1.0) * 0.5);

	    // パンニングと音の強さを考慮した最終的な音量を計算
	    return panning * adjustedVolume;
	};
	double Panning(const double _dotproduct_, const double _lisdirveclen_, const double _diffveclen_, const double _dotproductdir_, const double _plydirveclen_, const double _atten_max_, const double _attenuate_)
	{
	    // 長さの逆数を計算
	    double invListenerDirLength = 1.0 / _lisdirveclen_;
	    double invSourceVecLength = 1.0 / _diffveclen_;

	    // パンニング角度を計算（-1.0から1.0の範囲）
	    double panning = _dotproduct_ * invListenerDirLength * invSourceVecLength;

	    // パンニングの値を0.0から1.0の範囲にマッピング
	    panning = (panning + 1.0) * 0.5;

	    // リスナーの向きと音源の向きの内積を計算
	    double dotProductDir = _dotproductdir_;

	    // リスナーの向きと音源の向きの長さを計算
	    double sourceDirLength = _plydirveclen_;

	    // 長さの逆数を計算
	    double invSourceDirLength = 1.0 / sourceDirLength;

	    // 音源の向きとリスナーの向きの間の角度を計算（-1.0から1.0の範囲）
	    double directionality = dotProductDir * invListenerDirLength * invSourceDirLength;

	    // 音の強さを調整
	    double adjustedVolume = _attenuate_ + (_atten_max_ - _attenuate_) * ((directionality + 1.0) * 0.5);

	    // パンニングと音の強さを考慮した最終的な音量を計算
	    return panning * adjustedVolume;

	};

};

