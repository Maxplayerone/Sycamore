#include"LineAndOOBB.h"
#include"../Utils.h"

bool SM_Tests::Test_LAO_Valid() {
	SM_Physics::Box2D oobb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(3.0f, -2.0f);
	line.end = SM_math::vec2(11.0f, 4.0f);

	return SM_Physics::Intersection_LineAndOOBB(line, oobb);
}
bool SM_Tests::Test_LAO_Invalid() {
	SM_Physics::Box2D oobb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(-4.0f, -4.0f);
	line.end = SM_math::vec2(4.0f, -1.0f);

	return !SM_Physics::Intersection_LineAndOOBB(line, oobb);
}
bool SM_Tests::Test_LAO_Starting_In_OOBB() {
	SM_Physics::Box2D oobb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(6.0f, 4.0f);
	line.end = SM_math::vec2(11.0f, 4.0f);

	return SM_Physics::Intersection_LineAndOOBB(line, oobb);
}
bool SM_Tests::Test_LAO_Line_Too_Short() {
	SM_Physics::Box2D oobb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(-5.0f, -4.0f);
	line.end = SM_math::vec2(3.0f, 0.0f);

	return !SM_Physics::Intersection_LineAndOOBB(line, oobb);
}
bool SM_Tests::Test_LAO_Line_With_Zero_Coords() {
	SM_Physics::Box2D oobb(SM_math::vec2(2.0f, 2.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(0.0f, 0.0f);
	line.end = SM_math::vec2(10.0f, 10.0f);

	return SM_Physics::Intersection_LineAndOOBB(line, oobb);
}

bool SM_Tests::Test_LAO_Rotated_Valid() {
	SM_Physics::Box2D oobb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	oobb.rb.SetRotation(45.0f);
	DebugDraw::DebugLine2D line;	
	line.start = SM_math::vec2(0.0f, 0.0f);
	line.end = SM_math::vec2(5.0f, 5.0f);

	return SM_Physics::Intersection_LineAndOOBB(line, oobb);
}

//this test doesn't work
bool SM_Tests::Test_LAO_Rotated_Invalid() {
	SM_Physics::Box2D oobb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	oobb.rb.SetRotation(30.0f);
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(3.0f, -2.0f);
	line.end = SM_math::vec2(11.0f, 4.0f);

	return SM_Physics::Intersection_LineAndOOBB(line, oobb);
}