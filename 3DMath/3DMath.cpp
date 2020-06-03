// 3DMath.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Vector3.h"
#include "Matrix3X3.h"
using namespace std;

void print_v(Vector3 &v)
{
	cout << "[" << v.x << "," << v.y << "," << v.z << "]" << endl;
}

void print_m(Matrix3X3 &m)
{
	cout << m.m11 << "\t" << m.m12 << "\t" << m.m13 << endl;
	cout << m.m21 << "\t" << m.m22 << "\t" << m.m23 << endl;
	cout << m.m31 << "\t" << m.m32 << "\t" << m.m33 << endl;
}

int main()
{
	cout << "Hello Matrix3X3!\n";

	Matrix3X3 a, b, c;
	a.m11 = 1; a.m12 = -5; a.m13 = 3;
	a.m21 = 0; a.m22 = -2; a.m23 = 6;
	a.m31 = 7; a.m32 = 2; a.m33 = -4;

	b.m11 = -8; b.m12 = 6; b.m13 = 1;
	b.m21 = 7; b.m22 = 0; b.m23 = -3;
	b.m31 = 2; b.m32 = 4; b.m33 = 5;

	c = a * b;
	print_m(c);

	Vector3 v(3, -1, 4);

	Vector3 r;
	r = v * c;
	print_v(r);
	system("pause");
	return 0;
}


