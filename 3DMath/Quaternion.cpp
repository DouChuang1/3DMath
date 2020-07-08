#include "pch.h"
#include "Quaternion.h"
#include <math.h>
#include <assert.h>
#include "MathUtil.h"
#include "RotationMatrix.h"
#include "EulerAngles.h"

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

void Quaternion::fromRotationMatrix(const RotationMatrix &m)
{
	float m11 = m.m11;
	float m12 = m.m12;
	float m13 = m.m13;

	float m21 = m.m21;
	float m22 = m.m22;
	float m23 = m.m23;

	float m31 = m.m31;
	float m32 = m.m32;
	float m33 = m.m33;

	//计算 四元数中 w x y z 谁最大 经验算法 哪一个大 然后用这个值用另外一组公式去计算其他三个数值
	float fourWsqrtMinus1 = m11 + m22 + m33;
	float fourXsqrtMinus1 = m11 - m22 - m33;
	float fourYsqrtMinus1 = m22 - m11 - m33;
	float fourZsqrtMinus1 = m33 - m11 - m22;

	int biggest = fourWsqrtMinus1;
	int index = 0;
	if (fourXsqrtMinus1 > biggest)
	{
		biggest = fourXsqrtMinus1;
		index = 1;
	}
	if (fourYsqrtMinus1 > biggest)
	{
		biggest = fourYsqrtMinus1;
		index = 2;
	}
	if (fourZsqrtMinus1 > biggest)
	{
		biggest = fourZsqrtMinus1;
		index = 3;
	}
	
	float biggestVal = sqrt(biggest + 1.0f)*0.5f;
	float mult = 0.25  / biggestVal;
	switch (index)
	{
	case 0:
		w = biggestVal;
		x = (m23 - m32)*mult;
		y = (m31 - m13)*mult;
		z = (m12 - m21)*mult;
		break;
	case 1:
		x = biggestVal;
		w = (m23 - m32)*mult;
		y = (m12 + m21)*mult;
		z = (m31 + m13)*mult;
		break;
	case 2:
		y = biggestVal;
		w = (m31 - m13)*mult;
		x = (m12 + m21)*mult;
		z = (m23 + m32)*mult;
		break;
	case 3:
		z = biggestVal;
		w = (m12 - m21)*mult;
		x = (m31 + m13)*mult;
		y = (m23 + m32)*mult;
		break;
	default:
		break;
	}
}

void Quaternion::setToRatoteObjectToInertial(const EulerAngles &orientation)
{
	float sp, sb, sh;
	float cp, cb, ch;

	SinCos(&sp, &cp, orientation.pitch*0.5f);
	SinCos(&sb, &cb, orientation.bank*0.5f);
	SinCos(&sh, &ch, orientation.heading*0.5f);

	w = ch * cp*cb + sh * sp*sb;
	x = ch * sp*cb*+sh * cp*sb;
	y = sh * cp*cb - ch * sp*sb;
	z = ch * cp*sb - sh * sp*cb;
}

void Quaternion::setToRatoteInertialToObject(const EulerAngles &orientation)
{
	//上面的共轭
	float sp, sb, sh;
	float cp, cb, ch;

	SinCos(&sp, &cp, orientation.pitch*0.5f);
	SinCos(&sb, &cb, orientation.bank*0.5f);
	SinCos(&sh, &ch, orientation.heading*0.5f);

	w = ch * cp*cb + sh * sp*sb;
	x = -ch * sp*cb*-sh * cp*sb;
	y = -sh * cp*cb + ch * sp*sb;
	z = -ch * cp*sb + sh * sp*cb;
}

Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
	if (t <= 0)
	{
		return q0;
	}
	if (t >=1)
	{
		return q1;
	}

	//计算夹角Omega 点乘cos
	float cosOmega = dotProduct(q0, q1);

	//检查cosOmega 如果小于0 修改一个四元数为相反的 插值避免计算结果不一致

	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	if (cosOmega < 0)
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}
	float k0;
	float k1;
	//计算k0 k1
	//如果夹角足够小 可以使用线性插值
	if (cosOmega > 0.99999f)
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float sinOmega = sqrt(1 - cosOmega * cosOmega);
		float omega = atan2(sinOmega, cosOmega);
		float oneOverSinOmega = 1.0f / sinOmega;

		k0 = sin((1.0f - t)*omega)*oneOverSinOmega;
		k1 = sin(t*omega)*oneOverSinOmega;
	}

	Quaternion result;
	result.w = k0 * q0.w + k1 * q1w;
	result.x = k0 * q0.x + k1 * q1x;
	result.y = k0 * q0.y + k1 * q1y;
	result.z = k0 * q0.z + k1 * q1z;

	return result;
}