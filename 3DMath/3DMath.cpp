// 3DMath.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Vector3.h"
#include "Matrix4X3.h"
#include "MathUtil.h"
#include <math.h>
#include "RotationMatrix.h"
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

void print_m(Matrix4X3 &m)
{
	cout << to_zero(m.m11) << "\t" << to_zero(m.m12) << "\t" << to_zero(m.m13) << endl;
	cout << to_zero(m.m21) << "\t" << to_zero(m.m22) << "\t" << to_zero(m.m23) << endl;
	cout << to_zero(m.m31) << "\t" << to_zero(m.m32) << "\t" << to_zero(m.m33) << endl;
}

int main()
{
	cout << "Hello Rotation Matrix !\n";

	RotationMatrix rm;
	rm.m11 = 0.866f; rm.m12 = 0; rm.m13 =-0.5f;
	rm.m21 = 0.0f; rm.m22 = 1.0f; rm.m23 = 0.0f;
	rm.m31 = 0.5f; rm.m32 = 0.0f; rm.m33 = 0.866f;

	Vector3 v(10, 20, 30);

	Vector3 r;

	r = rm.intertialToObject(v);
	print_v(r);
	r = rm.ObjectTointertial(r);
	print_v(r);
	system("pause");
	return 0;
}


