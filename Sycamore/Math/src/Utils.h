#pragma once
#include"vector.h"

namespace SM_math {
	//compares two float numbers with the precision epsilon
	bool Compare(float x, float y, float epsilon);
	bool Compare(SM_math::vec2& vec, SM_math::vec2& vec2, float epsilon);

	bool Compare(float x, float y);
	bool Compare(SM_math::vec2& vec, SM_math::vec2& vec2);
}
