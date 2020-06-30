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

float safeAcos(float x)
{
	if (x <= -1.0f)
	{
		return PI;
	}
	if(x >= 1.0f)
	{
		return 0;
	}

	return acos(x);
}