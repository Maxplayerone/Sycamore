#include"vector.h"

SM_math::vec2& SM_math::Rotate(SM_math::vec2& vector, float angleDegrees, SM_math::vec2& origin)
{
	float angle = angleDegrees * (3.1415f / 180.0f);
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	vector.x -= origin.x;
	vector.y -= origin.y;

	// rotate point
	float xnew = vector.x * c - vector.y * s;
	float ynew = vector.x * s + vector.y * c;

	// translate point back:
	vector.x = xnew + origin.x;
	vector.y = ynew + origin.y;
	return vector;
}

int SM_math::vec2::Lengthquared() {
	return x * x + y * y;
}

void SM_math::vec2::Normalize() {
	float magnitude = sqrt((x * x) + (y * y));

	x = x / magnitude;
	y = y / magnitude;
}