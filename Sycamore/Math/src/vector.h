#pragma once
#include"../../src/smpch.h"

namespace SM_math {
	
	struct vec2 {
		float x;
		float y;

		vec2() {
			x = 0.0f;
			y = 0.0f;
		}

		vec2(float num) {
			x = num;
			y = num;
		}

		vec2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		vec2& operator+(vec2& _vector) {
			return vec2(x + _vector.x, y + _vector.y);
		}

		vec2 operator+(int num) {
			return vec2(x + num, y + num);
		}

		vec2 operator+(float num) {
			return vec2(x + num, y + num);
		}

		vec2 operator-(vec2& _vector) {
			return vec2(x - _vector.x, y - _vector.y);
		}

		vec2 operator-(int num) {
			return vec2(x - num, y - num);
		}

		vec2 operator-(float num) {
			return vec2(x - num, y - num);
		}

		vec2 operator*(int num) {
			return vec2(x * num, y * num);
		}

		vec2 operator*(float num) {
			return vec2(x * num, y * num);
		}

		vec2 operator/(float num) {
			return vec2(x / num, y / num);
		}

		float operator*(SM_math::vec2& other) {
			return x * other.x + y * other.y;
		}

		int Lengthquared();
		//normalizes the vector
		//(that means it's magnitude is 1)
		void Normalize();

		friend std::ostream& operator<< (std::ostream& stream, const SM_math::vec2& vector) {
			stream << "[" << vector.x << " , " << vector.y << "]";
			return stream;
		}
	};

	vec2& Rotate(SM_math::vec2& vector, float angleInDegrees, SM_math::vec2& origin);

	struct vec3 {
		float x;
		float y;
		float z;

		vec3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		vec3 operator+(vec3& _vector) {
			return vec3(x + _vector.x, y + _vector.y, z + _vector.z);
		}

		vec3 operator+(int num) {
			return vec3(x + num, y + num, z + num);
		}

		vec3 operator+(float num) {
			return vec3(x + num, y + num, z + num);
		}

		vec3 operator-(vec3& _vector) {
			return vec3(x - _vector.x, y - _vector.y, z + _vector.z);
		}

		vec3 operator-(int num) {
			return vec3(x - num, y - num, z - num);
		}

		vec3 operator-(float num) {
			return vec3(x - num, y - num, z - num);
		}

		vec3 operator*(int num) {
			return vec3(x * num, y * num, z * num);
		}

		vec3 operator*(float num) {
			return vec3(x * num, y * num, z * num);
		}

		friend std::ostream& operator<< (std::ostream& stream, const SM_math::vec3& vector) {
			stream << "[" << vector.x << " , " << vector.y <<  " , " << vector.z <<  "]";
			return stream;
		}
	};

	struct vec4 {
		float x;
		float y;
		float z;
		float w;

		vec4(float _x, float _y, float _z,float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		vec4(SM_math::vec2 v2, float _z, float _w) {
			x = v2.x;
			y = v2.y;
			z = _z;
			w = _w;
		}

		vec4(float num) {
			x = num;
			y = num;
			z = num;
			w = num;
		}

		friend std::ostream& operator<< (std::ostream& stream, const SM_math::vec4& vector) {
			stream << "[" << vector.x << " , " << vector.y << " , " << vector.z << " , " << vector.w << "]";
			return stream;
		}
	};
}

