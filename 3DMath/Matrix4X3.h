#pragma once

#include "Vector3.h"

class Matrix4X3 {
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
	float tx, ty, tz;

	void SetRotate(int x, float theta);
	void SetScale(const Vector3 &v);
	void SetProject(const Vector3 &v);
	void SetReflect(int x, float k);
	void SetReflect( Vector3 &v);
	void SetShear(int x,float s,float t);

	void ZeroTranslation();
	void SetTranslation(const Vector3 &v);
	void SetupTranslation(const Vector3 &v);
};

Matrix4X3 operator*(const Matrix4X3 &m1, const Matrix4X3 &m2);

Vector3 operator*(const Vector3 &v, const Matrix4X3 &m);

float Determinant(const Matrix4X3 &m);

Matrix4X3 Inverse(const Matrix4X3 &m);

Vector3 GetTranslation(const Matrix4X3 &m);