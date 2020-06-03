#include "pch.h"
#include "Matrix3X3.h"
#include "Vector3.h"

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