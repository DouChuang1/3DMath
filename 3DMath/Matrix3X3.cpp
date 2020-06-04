#include "pch.h"
#include "Matrix3X3.h"
#include "Vector3.h"
#include "MathUtil.h"
#include <assert.h>

Matrix3X3 operator*(const Matrix3X3 &m1, const Matrix3X3 &m2)
{
	Matrix3X3 r;
	r.m11 = m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31;
	r.m12 = m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32;
	r.m13 = m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33;

	r.m21 = m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31;
	r.m22 = m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32;
	r.m23 = m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33;

	r.m31 = m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31;
	r.m32 = m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32;
	r.m33 = m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33;
	return r;
}

Vector3 operator*(const Vector3 &v, const Matrix3X3 &m)
{
	return  Vector3(v.x*m.m11 + v.y*m.m21 + v.z*m.m31, v.x*m.m12 + v.y*m.m22 + v.z*m.m32, v.x*m.m13 + v.y*m.m23 + v.z*m.m33);
}

//1,2,3代表 x y z旋转
void Matrix3X3::SetRotate(int x, float theta)
{
	float s, c;
	SinCos(&s, &c, theta);
	switch (x)
	{
	case 1:
		m11 = 1; m12 = 0; m13 = 0;
		m21 = 0; m22 = c; m23 = s;
		m31 = 0; m32 = -s; m33 = c;
		break;
	case 2:
		m11 = c; m12 = 0; m13 = -s;
		m21 = 0; m22 = 1; m23 = 0;
		m31 = s; m32 = 0; m33 = c;
		break;
	case 3:
		m11 = c; m12 = s; m13 = 0;
		m21 = -s; m22 = c; m23 = 0;
		m31 = 0; m32 = 0; m33 = 1;
		break;
	default:
		break;
	}
}

//缩放矩阵
void Matrix3X3::SetScale(const Vector3 &v)
{
	m11 = v.x; m12 = 0; m13 = 0;
	m21 = 0; m22 = v.y; m23 = 0;
	m31 = 0; m32 = 0; m33 = v.z;
}

//投影矩阵 v传入单位向量 
void Matrix3X3::SetProject(const Vector3 &v)
{
	m11 = 1.0f - v.x*v.x;
	m22 = 1.0f - v.y*v.y;
	m33 = 1.0f - v.z*v.z;

	m12 = m21 = -v.x*v.y;
	m13 = m31 = -v.x*v.z;
	m23 = m32 = -v.y*v.z;
}

//1,2,3代表 x y z镜像
void Matrix3X3::SetReflect(int x)
{
	switch (x)
	{
	case 1:
		m11 = -1; m12 = 0; m13 = 0;
		m21 = 0; m22 = 1; m23 = 0;
		m31 = 0; m32 = 0; m33 = 1;
		break;
	case 2:
		m11 = 1; m12 = 0; m13 = 0;
		m21 = 0; m22 = -1; m23 = 0;
		m31 = 0; m32 = 0; m33 = 1;
		break;
	case 3:
		m11 = 1; m12 = 0; m13 = 0;
		m21 = 0; m22 = 1; m23 = 0;
		m31 = 0; m32 = 0; m33 = -1;
		break;
	default:
		break;
	}
}

void Matrix3X3::SetReflect( Vector3 &n)
{
	assert(fabs(n*n) - 1.0f < 0.01f);

	float ax = -2.0f*n.x;
	float ay = -2.0f*n.y;
	float az = -2.0f*n.z;

	m11 = 1.0f + ax * n.x;
	m22 = 1.0f + ay * n.y;
	m33 = 1.0f + az * n.z;

	m12 = m21 = ax * n.y;
	m13 = m31 = ax * n.z;
	m23 = m32 = ay * n.z;
}

//1，2，3代表用x，y，z轴切变
void Matrix3X3::SetShear(int x,float s,float t)
{
	switch (x)
	{
	case 1:
		m11 = 1; m12 = s; m13 = t;
		m21 = 0; m22 = 1; m23 = 0;
		m31 = 0; m32 = 0; m33 = 1;
		break;
	case 2:
		m11 = 1; m12 = 0; m13 = 0;
		m21 = s; m22 = 1; m23 = t;
		m31 = 0; m32 = 0; m33 = 1;
		break;
	case 3:
		m11 = 1; m12 = 0; m13 = 0;
		m21 = 0; m22 = 1; m23 = 0;
		m31 = s; m32 = t; m33 = 1;
		break;
	default:
		break;
	}
}