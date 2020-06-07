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
	cout << "Hello Matrix 行列式!\n";

	
	Matrix3X3 m;
	m.m11 = -4; m.m12 = -3; m.m13 = 3;
	m.m21 = 0; m.m22 = 2; m.m23 = -2;
	m.m31 = 1; m.m32 = 4; m.m33 = -1;

	float detM = Determinant(m);

	
	cout << detM << endl;

	Matrix3X3 r;
	r = Inverse(m);
	print_m(r);
	system("pause");
	return 0;
}


