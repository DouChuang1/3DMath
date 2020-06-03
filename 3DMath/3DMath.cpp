// 3DMath.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Vector3.h"
#include "Matrix3X3.h"
#include "MathUtil.h"
#include <math.h>
using namespace std;

float to_zero(float n)
{
	if (abs(n) < 0.0001)
	{
		return 0;
	}
	return n;
}

void print_v(Vector3 &v)
{
	cout << "[" << to_zero(v.x) << "," << to_zero(v.y) << "," << to_zero(v.z) << "]" << endl;
}

void print_m(Matrix3X3 &m)
{
	cout << to_zero(m.m11) << "\t" << to_zero(m.m12) << "\t" << to_zero(m.m13) << endl;
	cout << to_zero(m.m21) << "\t" << to_zero(m.m22) << "\t" << to_zero(m.m23) << endl;
	cout << to_zero(m.m31) << "\t" << to_zero(m.m32) << "\t" << to_zero(m.m33) << endl;
}

int main()
{
	cout << "Hello Matrix Rotate!\n";

	Vector3 v(10, 0, 0);
	Matrix3X3 m;
	m.SetRotate(3, PiOver2);
	Vector3 r;
	r = v * m;
	print_v(r);

	m.SetRotate(2, PiOver2);
	Vector3 w;
	w = v * m;
	print_v(w);

	m.SetRotate(1, PiOver2);
	Vector3 z;
	z = v * m;
	print_v(z);

	system("pause");
	return 0;
}


