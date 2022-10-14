#include"DataTypes.h"

std::ostream& operator<< (std::ostream& stream, const color3 color) {
	stream << "{" << color.r << " , " << color.g << " , " << color.b << "}";
	return stream;
}

std::ostream& operator<< (std::ostream& stream, const color4 color) {
	stream << "{" << color.r << " , " << color.g << " , " << color.b << " , " << color.a << "}";
	return stream;
}

color3& RandomColor() {
	color3 color;
	color.r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/ (0.1f, 1.0f));
	color.g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (0.1f, 1.0f));
	color.b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (0.1f, 1.0f));

	return color;
}