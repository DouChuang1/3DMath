#pragma once
#include "pch.h"
#include <math.h>

const float PI = 3.141593;
const float Pi2 = 2 * PI;
const float PiOver2 = PI / 2;

inline void SinCos(float *Sin, float *Cos, float theta)
{
	*Sin = sin(theta);
	*Cos = cos(theta);
}