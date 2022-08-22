#include"matrix.h"

std::ostream& SM_math::operator<< (std::ostream& stream, SM_math::mat4 matrix) {
	stream << std::endl;
	for (uint column = 0; column < 4; column++) {
		stream << "[ " << matrix.matrix4[0][column] << " " << matrix.matrix4[1][column] << " " << matrix.matrix4[2][column] << " " << matrix.matrix4[3][column] << " ]" << std::endl;
	}
	return stream;
}