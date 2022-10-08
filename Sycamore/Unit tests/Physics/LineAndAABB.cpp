#include"LineAndAABB.h"
#include"../Utils.h"

bool SM_Tests::Test_LAA_Valid() {
	SM_Physics::AABB aabb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(3.0f, -2.0f);
	line.end = SM_math::vec2(11.0f, 4.0f);

	return SM_Physics::Intersection_LineAndAABB(line, aabb);
}
bool SM_Tests::Test_LAA_Invalid() {
	SM_Physics::AABB aabb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(-4.0f, -4.0f);
	line.end = SM_math::vec2(4.0f, -1.0f);

	return !SM_Physics::Intersection_LineAndAABB(line, aabb);
}
bool SM_Tests::Test_LAA_Starting_In_AABB() {
	SM_Physics::AABB aabb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(6.0f, 4.0f);
	line.end = SM_math::vec2(11.0f, 4.0f);

	return SM_Physics::Intersection_LineAndAABB(line, aabb);
}
bool SM_Tests::Test_LAA_Line_Too_Short() {
	SM_Physics::AABB aabb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(-5.0f, -4.0f);
	line.end = SM_math::vec2(3.0f, 0.0f);

	return !SM_Physics::Intersection_LineAndAABB(line, aabb);
}
bool SM_Tests::Test_LAA_Line_With_Zero_Coords() {
	SM_Physics::AABB aabb(SM_math::vec2(2.0f, 2.0f), SM_math::vec2(8.0f, 8.0f));
	DebugDraw::DebugLine2D line;
	line.start = SM_math::vec2(0.0f, 0.0f);
	line.end = SM_math::vec2(10.0f, 10.0f);

	return SM_Physics::Intersection_LineAndAABB(line, aabb);
}