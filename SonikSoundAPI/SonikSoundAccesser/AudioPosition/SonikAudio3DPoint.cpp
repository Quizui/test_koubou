/*
 * SonikAudio3DPoint.cpp
 *
 *  Created on: 2024/01/04
 *      Author: SONIC
 */

#include "SonikAudio3DPoint.h"
#include "../../../MathBit/SonikMathStandard.h"


namespace SonikAudioPoint
{

	SonikAudio3DPoint::SonikAudio3DPoint(double _x_, double _y_, double _z_)
	:SonikMath::Sonik3DPoint(_x_, _y_, _z_)
	,ref_m_x(m_x)
	,ref_m_y(m_y)
	,ref_m_z(m_z)
	,mp_x(&m_x)
	,mp_y(&m_y)
	,mp_z(&m_z)
	{

	};

	SonikAudio3DPoint::~SonikAudio3DPoint(void)
	{

	};

	double SonikAudio3DPoint::Distance(const SonikAudio3DPoint& _point_)
	{
		double _distance[3];

		_distance[0] = (*_point_.mp_x) - (*mp_x);
		_distance[1] = (*_point_.mp_y) - (*mp_y);
		_distance[2] = (*_point_.mp_z) - (*mp_z);

		return SonikMath::sqrt( _distance[0] * _distance[0] + _distance[1] * _distance[1] + _distance[2] * _distance[2]);
	};

	double SonikAudio3DPoint::Distance(const double _x_, const double _y_, const double _z_)
	{
		double _distance[3];

		_distance[0] = _x_ - (*mp_x);
		_distance[1] = _y_ - (*mp_y);
		_distance[2] = _z_ - (*mp_z);

		return SonikMath::sqrt( _distance[0] * _distance[0] + _distance[1] * _distance[1] + _distance[2] * _distance[2]);
	};



};




