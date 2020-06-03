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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
