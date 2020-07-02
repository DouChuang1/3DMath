#pragma once
#include "Vector3.h"
class Quaternion
{
public:
	float w, x, y, z;

	void Identify() { w = 1; x = 0;  y = 0; z = 0; } //单位四元数

	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const Vector3 &axis,float theta);

	float getRotationAngle() const;
	Vector3 getRotationAxis() const;

	Quaternion operator *(const Quaternion &q) const;

	Quaternion &operator *=(const Quaternion &q);

	void normalize(); //规范化
};

extern const Quaternion kQuaternionIdentify;

extern float dotProduct(const Quaternion &a, const Quaternion &b);

extern Quaternion conjugate(const Quaternion &q); //共轭

extern Quaternion pow(const Quaternion &q, float exp); //幂计算