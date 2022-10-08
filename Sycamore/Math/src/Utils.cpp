#include"Utils.h"
#include<cstdlib>

bool SM_math::Compare(float x, float y, float epsilon) {
	return abs(x - y) <= epsilon * fmax(1.0f, fmax(abs(x), abs(y)));
}

bool SM_math::Compare(SM_math::vec2& vec, SM_math::vec2& vec2, float epsilon) {
	return Compare(vec.x, vec2.x, epsilon) && Compare(vec.y, vec2.y, epsilon);
}

bool SM_math::Compare(float x, float y) {
	return abs(x - y) <=  FLT_MIN  * fmax(1.0f, fmax(abs(x), abs(y)));
}

bool SM_math::Compare(SM_math::vec2& vec, SM_math::vec2& vec2) {
	return Compare(vec.x, vec2.x, FLT_MIN) && Compare(vec.y, vec2.y, FLT_MIN);
}

float SM_math::MaxValue(float a, float b) {
	return (a > b) ? a : b;
}

float SM_math::MinValue(float a, float b) {
	return (a < b) ? a : b;
}