#include"vector.h"

SM_math::vec2& SM_math::Rotate(SM_math::vec2& vector, float angleInDegrees, SM_math::vec2& origin) {
	//angle in radians
	float angle = angleInDegrees * 3.14159 / 180;
	SM_math::vec2 rotatedVector(1.0f);
	float translatedX =  vector.x - origin.x;
	float translatedY = vector.y - origin.y;

	/*
	if (angleInDegrees == 90) {
		rotationMatrix.m4[0][0] = 0;
		rotationMatrix.m4[1][0] = 1;
		rotationMatrix.m4[0][1] = -1;
		rotationMatrix.m4[1][1] = 0;
	}
	else if (angleInDegrees == 180) {
		rotationMatrix.m4[0][0] = -1;
		rotationMatrix.m4[1][0] = 0;
		rotationMatrix.m4[0][1] = 0;
		rotationMatrix.m4[1][1] = 1;
	}
	else if (angleInDegrees == 270) {
		rotationMatrix.m4[0][0] = 0;
		rotationMatrix.m4[1][0] = -1;
		rotationMatrix.m4[0][1] = 1;
		rotationMatrix.m4[1][1] = 0;
	}
	else {
		rotatedVector.x = (vector.x * cos(angle)) - (vector.x * sin(angle));
		rotatedVector.y = (vector.y * sin(angle)) + (vector.y * cos(angle));
		
	}
	*/
	rotatedVector.x = (translatedX * cos(angle)) - (translatedX  * sin(angle));
	rotatedVector.y = (translatedY * sin(angle)) + (translatedY * cos(angle));

	rotatedVector.x += origin.x;
	rotatedVector.y += origin.y;

	return rotatedVector;
}

int SM_math::vec2::Lengthquared() {
	return x * x + y * y;
}