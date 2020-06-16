#include "pch.h"
#include "MathUtil.h"
#include <math.h>

float wrapPi(float theta)
{
	theta = theta + PI;
	theta -= floor(theta*k1Over2Pi)*Pi2;
	theta -= PI;
	return theta;
}