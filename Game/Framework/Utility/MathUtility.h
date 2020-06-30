#pragma once

// <namespace name  : MathUtility>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef MATH_UTILITY_DEFINED
#define MATH_UTILITY_DEFINED

namespace MathUtility
{
	// <最小値未満かどうか>
	template <typename T>
	inline T Min(T min, T value)
	{
		if (min >= value)return min;
		return value;
	}

	// <最大値より大きいかどうか>
	template <typename T>
	inline T Max(T max, T value)
	{
		if (max <= value)return max;
		return value;
	}

	// <min～maxの間にvalueを収める>
	template <typename T>
	inline T Clamp(T min, T max, T value)
	{
		return Max(max, (Min(min, value)));
	}

	// <0～maxの範囲でxは何％の位置にいるか（範囲外は範囲内に収められる）>
	float Percentage(float x, float max);
	// <min～maxの範囲でxは何％の位置にいるか（範囲外は範囲内に収められる）>
	float Percentage(float x, float min, float max);

	// <0～maxの範囲でのpercent（％）の位置>
	float Lerp(float percent, float max);
	// <min～maxの範囲でのpercent（％）の位置>
	float Lerp(float percent, float min, float max);
}

#endif