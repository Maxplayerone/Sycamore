#pragma once
#include"vector.h"

namespace SM_math {
	//compares two float numbers with the precision epsilon
	bool Compare(float x, float y, float epsilon);
	bool Compare(SM_math::vec2& vec, SM_math::vec2& vec2, float epsilon);

	bool Compare(float x, float y);
	bool Compare(SM_math::vec2& vec, SM_math::vec2& vec2);

	float MaxValue(float a, float b);
	float MinValue(float a, float b);

	float Abs(float x);

	float Length(SM_math::vec2& vec);

	SM_math::vec2& Normalize(SM_math::vec2& vec, float length);
}
