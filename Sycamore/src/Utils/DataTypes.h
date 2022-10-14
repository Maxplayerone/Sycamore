#pragma once
#include"../smpch.h"

typedef unsigned int uint;

struct F4 {
	const float left;
	const float right;
	const float bottom;
	const float top;
};


struct color3 {
	float r;
	float g;
	float b;

	color3(float a, float c, float d) {
		r = a;
		g = c;
		b = d;
	}

	color3() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	}
};

color3& RandomColor();

std::ostream& operator<< (std::ostream& stream, const color3 color);

struct color4 {
	float r;
	float g;
	float b;
	float a;
};

std::ostream& operator<< (std::ostream& stream, const color4 color);