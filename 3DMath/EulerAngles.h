#pragma once
#include "RotationMatrix.h"
#include "Matrix4X3.h"


class EulerAngles
{
public :
	float heading;
	float pitch;
	float bank;

	EulerAngles(){}

	EulerAngles(float h,float p,float b):heading(h),pitch(p),bank(b){}

	void FromObjectToWorldMatrix(const Matrix4X3 &m);
	void FromWorldToObjectMatrix(const Matrix4X3 &m);
	void FromRotationMatrix(const RotationMatrix &r);

	void canonize(); // 三个角度限制 一定程度避免万向死锁问题
};