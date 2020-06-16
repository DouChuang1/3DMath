
#include "pch.h"
#include "MathUtil.h"
#include "EulerAngles.h"

void EulerAngles::FromObjectToWorldMatrix(const Matrix4X3 &m)
{
	//pitch正负九十度发生万向死锁
	float sp = -m.m32;
	if (fabs(sp) > 0.999999f) //检测万像死锁
	{
		pitch = PiOver2 * sp;
		bank = 0.0f;
		heading = atan2(-m.m23, m.m11);
	}
	else
	{
		heading = atan2(m.m31, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12, m.m22);
	}
}

void EulerAngles::FromWorldToObjectMatrix(const Matrix4X3 &m)
{
	//pitch正负九十度发生万向死锁
	float sp = -m.m23;
	if (fabs(sp) > 0.999999f) //检测万像死锁
	{
		pitch = PiOver2 * sp;
		bank = 0.0f;
		heading = atan2(-m.m31, m.m11);
	}
	else
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

void EulerAngles::FromRotationMatrix(const RotationMatrix &m)
{
	//pitch正负九十度发生万向死锁
	float sp = -m.m23;
	if (fabs(sp) > 0.999999f) //检测万像死锁
	{
		pitch = PiOver2 * sp;
		bank = 0.0f;
		heading = atan2(-m.m31, m.m11);
	}
	else
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

void EulerAngles::canonize()
{
	pitch = wrapPi(pitch);
	if (pitch < -k1Over2Pi)
	{
		pitch = -PI - pitch;
		heading += PI;
		bank += PI;
	}
	else if (pitch > PiOver2)
	{
		pitch = PI - pitch;
		heading += PI;
		bank += PI;
	}

	if (fabs(pitch) > PiOver2 - 1e-4)
	{
		heading += bank;
		bank = 0.0f;
	}
	else
	{
		bank = wrapPi(bank);
	}
	heading = wrapPi(heading);
}