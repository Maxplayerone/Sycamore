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
};

std::ostream& operator<< (std::ostream& stream, const color3 color);

struct color4 {
	float r;
	float g;
	float b;
	float a;
};

std::ostream& operator<< (std::ostream& stream, const color4 color);