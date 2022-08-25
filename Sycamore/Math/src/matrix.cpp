#include"matrix.h"

std::ostream& SM_math::operator<< (std::ostream& stream, SM_math::mat4 matrix) {
	stream << std::endl;
	for (uint column = 0; column < 4; column++) {
		stream << "[ " << matrix.m4[0][column] << " " << matrix.m4[1][column] << " " << matrix.m4[2][column] << " " << matrix.m4[3][column] << " ]" << std::endl;
	}
	return stream;
}

SM_math::mat4 SM_math::ortho(float left, float right, float top, float bottom, float zNear, float zFar) {
	SM_math::mat4 matrix(1.0f);

	matrix.m4[0][0] = 2 / (right - left);
	matrix.m4[1][1] = 2 / (top - bottom);
	matrix.m4[2][2] = - 2 / (zFar - zNear);
	matrix.m4[3][0] = -(right + left) / (right - left);
	matrix.m4[3][1] = -(top + bottom) / (top - bottom);
	matrix.m4[3][2] = -(zFar + zNear) / (zFar - zNear);

	return matrix;
}

SM_math::mat4 SM_math::MatrixScale(SM_math::mat4 matrixToScale, float scaleFactor) {
	SM_math::mat4 matrix(scaleFactor);
	return matrixToScale * matrix;
}

SM_math::mat4& SM_math::MatrixRotation(SM_math::mat4& matrixToRotate, float _angle) {
	float angle = _angle * 3.14159 / 180;

	SM_math::mat4 rotationMatrix(1.0f);

	//ECGE CASES :DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	if (_angle == 90) {
		rotationMatrix.m4[0][0] = 0;
		rotationMatrix.m4[1][0] = 1;
		rotationMatrix.m4[0][1] = -1;
		rotationMatrix.m4[1][1] = 0;
		LOGGER_INFO("90");
	} 
	else if (_angle == 180) {
		rotationMatrix.m4[0][0] = -1;
		rotationMatrix.m4[1][0] = 0;
		rotationMatrix.m4[0][1] = 0;
		rotationMatrix.m4[1][1] = 1;
		LOGGER_INFO("180");
	}
	else if (_angle == 270) {
		rotationMatrix.m4[0][0] = 0;
		rotationMatrix.m4[1][0] = -1;
		rotationMatrix.m4[0][1] = 1;
 		rotationMatrix.m4[1][1] = 0;
		LOGGER_INFO("270");
	}
	else{

		rotationMatrix.m4[0][0] = cos(angle);
		rotationMatrix.m4[1][0] = sin(angle);
		rotationMatrix.m4[0][1] = -sin(angle);
		rotationMatrix.m4[1][1] = cos(angle);
		LOGGER_INFO("anything");
	}
	//we're not caring about the argument's matrix
	return rotationMatrix;
}