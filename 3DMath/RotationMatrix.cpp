
#include "pch.h"
#include "RotationMatrix.h"
void RotationMatrix::identify()
{
	m11 = 1; m12 = 0; m13 = 0;
	m21 = 0; m22 = 1; m23 = 0;
	m31 = 0; m32 = 0; m33 = 1;
}

Vector3 RotationMatrix::intertialToObject(const Vector3 &v) const
{
	return Vector3(v.x*m11 + v.y *m21 + v.z*m31, v.x*m12 + v.y *m22 + v.z*m32, v.x*m13 + v.y*m23 + v.z *m33);
}

//需要乘以旋转矩阵的逆矩阵 保证旋转矩阵是正交矩阵 转置矩阵=逆矩阵
Vector3 RotationMatrix::ObjectTointertial(const Vector3 &v) const
{
	return Vector3(v.x*m11 + v.y*m12 + v.z*m13, v.x*m21 + v.y *m22 + v.z*m23, v.x*m31 + v.y* m32 + v.z *m33);
}