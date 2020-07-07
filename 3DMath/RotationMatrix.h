#pragma once
#include "Vector3.h"
#include "Quaternion.h"
class EulerAngles;
class Quaternion;

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
	void fromInertialToObjectQuaternion(const Quaternion &q);
	void fromObjectToInertialQuaternion(const Quaternion &q);
};