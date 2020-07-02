#include "pch.h"
#include "Quaternion.h"
#include <math.h>
#include <assert.h>
#include "MathUtil.h"

const Quaternion kQuaternionIdentify = { 1.0f,0.0f,0.0f,0.0f };

void Quaternion::setToRotateAboutX(float theta)
{
	//计算半角
	float thetaOver2 = theta * 0.5f;
	//计算w 
	w = cos(thetaOver2);
	x = sin(thetaOver2)*1;
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
	//计算半角
	float thetaOver2 = theta * 0.5f;
	//计算w 
	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2) * 1;
	z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
	//计算半角
	float thetaOver2 = theta * 0.5f;
	//计算w 
	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2) * 1;
}

void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{
	assert(fabs(VecMag(axis) - 1.0f) < 0.01f);

	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sin(thetaOver2);

	w = cos(thetaOver2);
	x = axis.x*sinThetaOver2;
	y = axis.y*sinThetaOver2;
	z = axis.z*sinThetaOver2;
}

//四元数算出旋转角
float Quaternion::getRotationAngle() const 
{
	//根据w 算出半角
	float thetaOver2 = safeAcos(w);
	
	return 2 * thetaOver2;
}

//四元数算出旋转轴
Vector3 Quaternion::getRotationAxis() const
{
	float sinThetaOver2Sq = 1.0f - w * w;
	float sinThetaOver2 = sqrt(sinThetaOver2Sq);

	float oneOverSinThetaOver2 = 1 / sinThetaOver2;
	float nx = x* oneOverSinThetaOver2;
	float ny = y * oneOverSinThetaOver2;
	float nz = z* oneOverSinThetaOver2;

	return Vector3(nx,ny,nz);
}

Quaternion Quaternion::operator*(const Quaternion &q) const
{
	Quaternion result;
	result.w = w * q.w - x * q.x - y * q.y - z * q.z;
	result.x = w * q.x + x * q.w + z * q.y - y * q.z;
	result.y = w * q.y + y * q.w + x * q.z - z * q.x;
	result.z = w * q.z + z * q.w + y * q.x - x * q.y;

	return result;
}

Quaternion &Quaternion::operator*=(const Quaternion &q)
{
	*this = *this*q;
	return *this;
}

void Quaternion::normalize()
{
	float mag = (float)sqrt(w*w + x * x + y * y + z * z);

	if (mag > 0.0f)
	{
		float oneOverMg = 1.0f / mag;
		w *= oneOverMg;
		x *= oneOverMg;
		y *= oneOverMg;
		z *= oneOverMg;
	}
	else
	{
		assert(false);
		Identify();
	}
}

float dotProduct(const Quaternion &a, const Quaternion &b)
{
	return a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;
}

//共轭
Quaternion conjugate(const Quaternion &q)
{
	Quaternion result;
	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
}

Quaternion pow(const Quaternion &q, float exp)
{
	if (fabs(q.w > 0.999999999f))
	{
		return q;
	}

	float alpha = acos(q.w);

	float newAlpha = exp * alpha;

	Quaternion result;
	result.w = cos(newAlpha);

	float mult = sin(newAlpha) / sin(alpha);

	result.x = q.x*mult;
	result.y = q.y*mult;
	result.z = q.z*mult;

	return result;
}