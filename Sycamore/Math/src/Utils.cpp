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

float SM_math::Abs(float x) {
	return (x < 0) ? -x : x;
}

SM_math::vec2&  SM_math::Abs(SM_math::vec2& vec) {
	return SM_math::vec2(Abs(vec.x), Abs(vec.y));
}

SM_math::mat2& SM_math::Abs(SM_math::mat2& mat) {
	return SM_math::mat2(Abs(mat.column1), Abs(mat.column2));
}


float SM_math::Length(SM_math::vec2& vec) {
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

SM_math::vec2& SM_math::Normalize(SM_math::vec2& vec, float length) {
	return SM_math::vec2(vec.x / length, vec.y / length);
}

float SM_math::Dot(const SM_math::vec2& a, const SM_math::vec2& b) {
	return a.x * b.x + a.y * b.y;
}

float SM_math::Sign(float x) {
	return x > 0.0f ? 1.0f : -1.0f;
}