#pragma once

class Vector3;

class Matrix3X3 {
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	void SetRotate(int x, float theta);
};

Matrix3X3 operator*(const Matrix3X3 &m1, const Matrix3X3 &m2);

Vector3 operator*(const Vector3 &v, const Matrix3X3 &m);
