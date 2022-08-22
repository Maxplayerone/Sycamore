#pragma once
typedef unsigned int uint;
#include"../../src/smpch.h"
#include"../../src/Utils/Logger.h"

namespace SM_math {

	struct mat4 {
		//			 row column
		float matrix4[4][4];

		mat4(float diagonalNumber) {
			uint diagonalOffset = 0;
			for (uint column = 0; column < 4; column++) {
				for (uint row = 0; row < 4; row++) {
					if (row == diagonalOffset) {
						LOGGER_INFO("Hello");
						matrix4[row][column] = diagonalNumber;
						diagonalOffset++;
					}
					matrix4[row][column] = 0.0f;
				}
			}
		}
	};

	std::ostream& operator<< (std::ostream& stream, SM_math::mat4 matrix);
}