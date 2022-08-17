#include"DataTypes.h"

std::ostream& operator<< (std::ostream& stream, const color3 color) {
	stream << "{" << color.r << " , " << color.g << " , " << color.b << "}";
	return stream;
}

std::ostream& operator<< (std::ostream& stream, const color4 color) {
	stream << "{" << color.r << " , " << color.g << " , " << color.b << " , " << color.a << "}";
	return stream;
}