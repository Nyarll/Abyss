#pragma once

// <namespace name  : MathUtility>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef MATH_UTILITY_DEFINED
#define MATH_UTILITY_DEFINED

namespace MathUtility
{
	// <�ŏ��l�������ǂ���>
	template <typename T>
	inline T Min(T min, T value)
	{
		if (min >= value)return min;
		return value;
	}

	// <�ő�l���傫�����ǂ���>
	template <typename T>
	inline T Max(T max, T value)
	{
		if (max <= value)return max;
		return value;
	}

	// <min�`max�̊Ԃ�value�����߂�>
	template <typename T>
	inline T Clamp(T min, T max, T value)
	{
		return Max(max, (Min(min, value)));
	}

	// <0�`max�͈̔͂�x�͉����̈ʒu�ɂ��邩�i�͈͊O�͔͈͓��Ɏ��߂���j>
	float Percentage(float x, float max);
	// <min�`max�͈̔͂�x�͉����̈ʒu�ɂ��邩�i�͈͊O�͔͈͓��Ɏ��߂���j>
	float Percentage(float x, float min, float max);

	// <0�`max�͈̔͂ł�percent�i���j�̈ʒu>
	float Lerp(float percent, float max);
	// <min�`max�͈̔͂ł�percent�i���j�̈ʒu>
	float Lerp(float percent, float min, float max);
}

#endif