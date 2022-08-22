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