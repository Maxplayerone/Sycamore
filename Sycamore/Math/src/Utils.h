#pragma once
#include"vector.h"
#include"matrix.h"

namespace SM_math {
	//compares two float numbers with the precision epsilon
	bool Compare(float x, float y, float epsilon);
	bool Compare(SM_math::vec2& vec, SM_math::vec2& vec2, float epsilon);

	bool Compare(float x, float y);
	bool Compare(SM_math::vec2& vec, SM_math::vec2& vec2);

	float MaxValue(float a, float b);
	float MinValue(float a, float b);

	float Abs(float x);
	SM_math::vec2& Abs(SM_math::vec2& vec);
	SM_math::mat2& Abs(SM_math::mat2& mat);

	float Length(SM_math::vec2& vec);

	SM_math::vec2& Normalize(SM_math::vec2& vec, float length);

	float Dot(const SM_math::vec2& a, const SM_math::vec2& b);
	float Sign(float x);
	template<typename T> inline void Swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}
}
