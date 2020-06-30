#include "pch.h"
#include "Quaternion.h"
#include <math.h>
#include <assert.h>
#include "MathUtil.h"

const Quaternion kQuaternionIdentify = { 1.0f,0.0f,0.0f,0.0f };

void Quaternion::setToRotateAboutX(float theta)
{
	//������
	float thetaOver2 = theta * 0.5f;
	//����w 
	w = cos(thetaOver2);
	x = sin(thetaOver2)*1;
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
	//������
	float thetaOver2 = theta * 0.5f;
	//����w 
	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2) * 1;
	z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
	//������
	float thetaOver2 = theta * 0.5f;
	//����w 
	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2) * 1;
}

void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{
	assert(fabs(VecMag(axis) - 1.0f) < 0.01f);

	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sin(thetaOver2);

	w = cos(thetaOver2);
	x = axis.x*sinThetaOver2;
	y = axis.y*sinThetaOver2;
	z = axis.z*sinThetaOver2;
}

//��Ԫ�������ת��
float Quaternion::getRotationAngle() const 
{
	//����w ������
	float thetaOver2 = safeAcos(w);
	
	return 2 * thetaOver2;
}

//��Ԫ�������ת��
Vector3 Quaternion::getRotationAxis() const
{
	float sinThetaOver2Sq = 1.0f - w * w;
	float sinThetaOver2 = sqrt(sinThetaOver2Sq);

	float oneOverSinThetaOver2 = 1 / sinThetaOver2;
	float nx = x* oneOverSinThetaOver2;
	float ny = y * oneOverSinThetaOver2;
	float nz = z* oneOverSinThetaOver2;

	return Vector3(nx,ny,nz);
}