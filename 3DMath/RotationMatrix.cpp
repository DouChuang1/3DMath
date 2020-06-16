
#include "pch.h"
#include "RotationMatrix.h"
#include "EulerAngles.h"
#include "MathUtil.h"

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

//欧拉角转换成矩阵(惯性到物体) 物体->惯性 BPH  惯性->物体 HPB 
void RotationMatrix::Setup(const EulerAngles &orientation)
{
	float sh, ch, sp, cp, sb, cb;
	SinCos(&sh, &ch, orientation.heading);
	SinCos(&sp, &cp, orientation.pitch);
	SinCos(&sb, &cb, orientation.bank);

	m11 = ch * cb + sh * sp*sb;
	m21 = sb * cp;
	m31 = -sh * cb + ch * sp*sb;
	m12 = -ch * sb + sh * sp*cb;
	m22 = cb * cp;
	m32 = sb * sh + ch * sp*cb;
	m13 = sh * cp;
	m23 = -sp;
	m33 = ch * cp;
}