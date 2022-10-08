#include"LineAndCircle.h"
#include"../Utils.h"

bool SM_Tests::Test_LAC_Valid() {
	SM_Physics::Circle circle(4.0f, 4.0f);
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(2.0f, 3.0f);
	line.end = SM_math::vec2(10.0f, 7.0f);
	// f(x) = 4,5x + 2

	return SM_Physics::Intersection_LineAndCircle(line, circle);
}
bool SM_Tests::Test_LAC_Invalid() {
	SM_Physics::Circle circle(4.0f, 4.0f);
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(2.0f, 20.0f);
	line.end = SM_math::vec2(10.0f, 60.0f);

	return !SM_Physics::Intersection_LineAndCircle(line, circle);
}
bool SM_Tests::Test_LAC_Start_In_Circle() {
	SM_Physics::Circle circle(4.0f, 4.0f);
	circle.SetRadius(2.0f);
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(4.0f, 4.0f);
	line.end = SM_math::vec2(6.0f, 6.0f);

	return SM_Physics::Intersection_LineAndCircle(line, circle);
}
bool SM_Tests::Test_LAC_Vertical_Line() {
	SM_Physics::Circle circle(4.0f, 4.0f);
	circle.SetRadius(2.0f);
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(5.0f, 4.0f);
	line.end = SM_math::vec2(5.0f, 100.0f);

	return SM_Physics::Intersection_LineAndCircle(line, circle);
}
bool SM_Tests::Test_LAC_Horizontal_Line() {
	SM_Physics::Circle circle(4.0f, 4.0f);
	circle.SetRadius(3.0f);
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(10.0f, 5.0f);
	line.end = SM_math::vec2(2.0f, 5.0f);

	return SM_Physics::Intersection_LineAndCircle(line, circle);
}