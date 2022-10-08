#include"vector.h"

SM_math::vec2& SM_math::Rotate(SM_math::vec2& vector, float angleInDegrees, SM_math::vec2& origin) {
	//angle in radians
	float angle = angleInDegrees * 3.14159 / 180;
	//float angle = angleInDegrees;
	SM_math::vec2 rotatedVector(1.0f);
	float translatedX =  vector.x - origin.x;
	float translatedY = vector.y - origin.y;

	rotatedVector.x = (translatedX * cos(angle)) - (translatedX  * sin(angle));
	rotatedVector.y = (translatedY * sin(angle)) + (translatedY * cos(angle));

	rotatedVector.x += origin.x;
	rotatedVector.y += origin.y;

	return rotatedVector;
}

int SM_math::vec2::Lengthquared() {
	return x * x + y * y;
}

void SM_math::vec2::Normalize() {
	float magnitude = sqrt((x * x) + (y * y));

	x = x / magnitude;
	y = y / magnitude;
}