
#include "pch.h"
#include "MathUtil.h"
#include "EulerAngles.h"
#include "Quaternion.h"

void EulerAngles::FromObjectToWorldMatrix(const Matrix4X3 &m)
{
	//pitch������ʮ�ȷ�����������
	float sp = -m.m32;
	if (fabs(sp) > 0.999999f) //�����������
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
	//pitch������ʮ�ȷ�����������
	float sp = -m.m23;
	if (fabs(sp) > 0.999999f) //�����������
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
	//pitch������ʮ�ȷ�����������
	float sp = -m.m23;
	if (fabs(sp) > 0.999999f) //�����������
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

void EulerAngles::fromObjectToIneritialQuaternion(const Quaternion&q)
{
	float sp = -2.0f*(q.y*q.z - q.w*q.x);
	//����Ƿ�ᷢ��������
	if (fabs(sp) > 0.99999f)
	{
		pitch = k1Over2Pi * sp;
		heading = atan2(-q.x*q.z + q.w*q.y,0.5f-q.y*q.y-q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		pitch = asin(sp);
		heading = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y + q.w*q.z, 0.5 - q.x*q.x - q.z*q.z);
	}
}

void EulerAngles::fromIneritialToObjectQuaternion(const Quaternion&q)
{
	//�෴�任 ��Ԫ������ ȡxyz ��Ӧ�ĸ���
	float sp = -2.0f*(q.y*q.z + q.w*q.x);
	//����Ƿ�ᷢ��������
	if (fabs(sp) > 0.99999f)
	{
		pitch = k1Over2Pi * sp;
		heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		pitch = asin(sp);
		heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y -q.w*q.z, 0.5 - q.x*q.x - q.z*q.z);
	}
}