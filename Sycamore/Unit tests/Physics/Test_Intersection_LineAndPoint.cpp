#include"Test_Intersection_LineAndPoint.h"

#include"../Utils.h"

bool SM_Tests::Test_Valid() {
	SM_math::vec2 point(2, 2);
	DebugDraw::DebugLine2D line;
	line.start = { 0, 0 };
	line.end = { 5, 5 };

	return SM_Physics::Intersection_LineAndPoint(point, line);
}

bool SM_Tests::Test_Point_Not_In_Line() {
	SM_math::vec2 point(2, 3);
	DebugDraw::DebugLine2D line;
	line.start = { 0, 0 };
	line.end = { 5, 5 };

	return !SM_Physics::Intersection_LineAndPoint(point, line);
}

bool SM_Tests::Test_Point_On_Line_Start() {
	DebugDraw::DebugLine2D line;
	line.start = { 0, 0 };
	line.end = { 5, 5 };
	SM_math::vec2 point(line.start);

	return SM_Physics::Intersection_LineAndPoint(point, line);
}
bool SM_Tests::Test_Line_Is_Vertical() {
	SM_math::vec2 point(0, 2);
	DebugDraw::DebugLine2D line;
	line.start = { 0, 0 };
	line.end = { 0, 20 };

	return SM_Physics::Intersection_LineAndPoint(point, line);
}
bool SM_Tests::Test_Line_Is_Horizontal() {
	SM_math::vec2 point(2, 0);
	DebugDraw::DebugLine2D line;
	line.start = { 0, 0 };
	line.end = { 20, 0 };

	return SM_Physics::Intersection_LineAndPoint(point, line);
}
bool SM_Tests::Test_Point_On_Negative_Coords() {
	SM_math::vec2 point(-25, -25);
	DebugDraw::DebugLine2D line;
	line.start = { 0, 0 };
	line.end = { -50, -50 };

	return SM_Physics::Intersection_LineAndPoint(point, line);
}