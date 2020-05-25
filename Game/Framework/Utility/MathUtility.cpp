#include "MathUtility.h"

float MathUtility::Percentage(float x, float max)
{
	float n = Clamp(x, 0.f, max);
	return (n / max);
}

float MathUtility::Percentage(float x, float min, float max)
{
	return Percentage(x - min, max - min);
}

float MathUtility::Lerp(float percent, float max)
{
	return max * percent;
}

float MathUtility::Lerp(float percent, float min, float max)
{
	return Lerp(percent, max - min) + min;
}
