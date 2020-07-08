#pragma once
#include "Vector3.h"

class RotationMatrix;
class EulerAngles;

class Quaternion
{
public:
	float w, x, y, z;

	void Identify() { w = 1; x = 0;  y = 0; z = 0; } //��λ��Ԫ��

	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const Vector3 &axis,float theta);

	float getRotationAngle() const;
	Vector3 getRotationAxis() const;

	Quaternion operator *(const Quaternion &q) const;

	Quaternion &operator *=(const Quaternion &q);

	void normalize(); //�淶��

	void fromRotationMatrix(const RotationMatrix &m);

	void setToRatoteObjectToInertial(const EulerAngles &orientation);  //ŷ����ת��Ԫ�� ��������ϵ����������ϵ

	void setToRatoteInertialToObject(const EulerAngles &orientation); //ŷ����ת��Ԫ�� ��������ϵ����������ϵ
};

extern const Quaternion kQuaternionIdentify;

extern float dotProduct(const Quaternion &a, const Quaternion &b);

extern Quaternion conjugate(const Quaternion &q); //����

extern Quaternion pow(const Quaternion &q, float exp); //�ݼ���

extern Quaternion slerp(const Quaternion &q1, const Quaternion &q2,float t); //��ֵ 0<t<1