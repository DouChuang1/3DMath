#pragma once
#include "pch.h"
#include <math.h>

const float PI = 3.141593;
const float Pi2 = 2 * PI;
const float PiOver2 = PI / 2;
const float k1Over2Pi = 1.0f / Pi2;
const float k1OverPi = 1.0f / PI;

extern float wrapPi(float theta);

inline void SinCos(float *Sin, float *Cos, float theta)
{
	*Sin = sin(theta);
	*Cos = cos(theta);
}