#pragma once
#include <math.h>

class Vector3
{
public:
	float x, y, z;

	Vector3() {}
	Vector3(const Vector3 &v) :x(v.x), y(v.y), z(v.z) {}
	Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}

	void Zero() { x = y = z = 0.0f; }

	Vector3 operator -() { return Vector3(-x, -y, -z); } //向量相减

	//向量标量相乘
	Vector3 operator *(float a)
	{
		return Vector3(a*x, a*y, a*z);
	}

	//向量标量相乘
	Vector3 operator /(float a)
	{
		float f = 1 / a;
		return Vector3(f*x, f*y, f*z);
	}

	//向量标量相乘
	void Normoalize()
	{
		float m = x * x + y * y + z * z;
		if (m > 0)
		{
			float f = 1 / sqrt(m);
			x *= f;
			y *= f;
			z *= f;
		}
	}

	//向量相加
	Vector3 operator +(Vector3 &v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	//向量相减
	Vector3 operator -(Vector3 &v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	//向量相加
	Vector3 operator +=(Vector3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	//向量相减
	Vector3 operator -=(Vector3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	//向量点乘
	float operator *(Vector3 &v) const
	{
		return (x*v.x + y * v.y + z * v.z);
	}
};

//向量模长
inline float VecMag(const Vector3 &v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

inline Vector3 operator *(float a, Vector3 &v)
{
	return Vector3(v.x*a, v.y*a, v.z*a);
}

inline float Distance(Vector3 &a, Vector3 &b)
{
	return VecMag(a - b);

}

inline Vector3 Cross(Vector3 &a, Vector3 &b)
{
	return Vector3(a.y*b.z - a.z - b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);

}

