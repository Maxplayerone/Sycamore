#pragma once
#include<iostream>

namespace SM_math {

	struct vec2 {
		float x;
		float y;

		vec2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		vec2 operator+(vec2& _vector) {
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

		friend std::ostream& operator<< (std::ostream& stream, const SM_math::vec2& vector) {
			stream << "[" << vector.x << " , " << vector.y << "]";
			return stream;
		}
	};

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
}
