#pragma once
#include "Vector3.h"
class EulerAngles;

class RotationMatrix
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	void identify(); //µ•Œªæÿ’Û

	Vector3 intertialToObject(const Vector3 &v) const;

	Vector3 ObjectTointertial(const Vector3 &v) const;

	void Setup(const EulerAngles &orientation);
};