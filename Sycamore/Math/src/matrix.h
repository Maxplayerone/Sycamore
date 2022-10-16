#pragma once
typedef unsigned int uint;

#include"../../src/smpch.h"

#include"../../src/Utils/Logger.h"

#include"vector.h"

namespace SM_math {

	struct mat2 {
		SM_math::vec2 column1;
		SM_math::vec2 column2;

		mat2() {
			//identity matrix
			column1.x = 1.0f;
			column1.y = 0.0f;
			column2.x = 0.0f;
			column2.y = 1.0f;
		}

		mat2(float angle) {
			float c = cosf(angle);
			float s = sinf(angle);

			column1.x = c;
			column1.y = s;
			column2.x = -s;
			column2.y = c;
		}

		mat2(SM_math::vec2& col1, SM_math::vec2& col2) {
			column1 = col1;
			column2 = col2;
		}

		mat2(float x1, float y1, float x2, float y2) {
			column1.x = x1;
			column1.y = y1;
			column2.x = x2;
			column2.y = y2;
		}

		mat2& Transpose() const {
			return mat2(SM_math::vec2(column1.x, column2.x), SM_math::vec2(column1.y, column2.y));
		}
	};

	SM_math::vec2& operator*(const mat2& mat, const vec2& vec);
	SM_math::mat2& operator*(const mat2& a, const mat2& b);


	struct mat4 {
		//			 row column
		float m4[4][4];

		mat4(float diagonalNumber) {
			uint diagonalOffset = 0;
			for (uint column = 0; column < 4; column++) {
				for (uint row = 0; row < 4; row++) {
					if (row == diagonalOffset && column == diagonalOffset) {
						m4[row][column] = diagonalNumber;
						diagonalOffset++;
					}
					else {
						m4[row][column] = 0.0f;
					}
				}
			}
		}

		SM_math::mat4& operator* (const SM_math::mat4& other) {
			SM_math::mat4 newMatrix(0.0f);
			float val1;
			float val2;
			float val3;
			float val4;

			for (int k = 0; k < 4; k++) {
				for (int j = 0; j < 4; j++) {
					val1 = m4[0][k] * other.m4[j][0];
					val2 = m4[1][k] * other.m4[j][1];
					val3 = m4[2][k] * other.m4[j][2];
					val4 = m4[3][k] * other.m4[j][3];

					newMatrix.m4[j][k] = val1 + val2 + val3 + val4;
				}
			}

			return newMatrix;
		}

		//column vect
		SM_math::vec4& operator* (const vec4& vector) {
			SM_math::vec4 newVector(0.0f);
			float val1;
			float val2;
			float val3;
			float val4;

			for (int j = 0; j < 4; j++) {
				val1 = m4[0][j] * vector.x;
				val2 = m4[1][j] * vector.y;
				val3 = m4[2][j] * vector.z;
				val4 = m4[3][j] * vector.w;

				float sum = val1 + val2 + val3 + val4;
				switch (j) {
				case 0:
					newVector.x = sum;
					break;
				case 1:
					newVector.y = sum;
					break;
				case 2:
					newVector.z = sum;
					break;
				case 3:
					newVector.w = sum;
					break;
				}
			}
			return newVector;
		}
		
		SM_math::vec2& operator* (const vec2& vector) {
			SM_math::vec2 newVector;
			float val1;
			float val2;

			for (int j = 0; j < 2; j++) {
				val1 = m4[0][j] * vector.x;
				val2 = m4[1][j] * vector.y;

				float sum = val1 + val2;
				switch (j) {
				case 0:
					newVector.x = sum;
					break;
				case 1:
					newVector.y = sum;
					break;
				}
			}
			return newVector;
		}
		
	};

	std::ostream& operator<< (std::ostream& stream, SM_math::mat4 matrix);

	SM_math::mat4 ortho(float left, float right, float top, float bottom, float zNear, float zFar);

	SM_math::mat4 MatrixScale(SM_math::mat4 matrixToScale, float scaleFactor);
	SM_math::mat4& MatrixRotation(SM_math::mat4& matrixToRotate, float angle);
}