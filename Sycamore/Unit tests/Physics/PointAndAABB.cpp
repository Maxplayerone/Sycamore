#include"PointAndAABB.h"
#include"../Utils.h"

bool SM_Tests::Test_PAA_Valid() {
	SM_Physics::AABB aabb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(4.0f, 7.0f);

	return SM_Physics::Intersection_PointAndAABB(point, aabb);
}
bool SM_Tests::Test_PAA_Invalid() {
	SM_Physics::AABB aabb(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(15.0f, -7.0f);

	return !SM_Physics::Intersection_PointAndAABB(point, aabb);
}
bool SM_Tests::Test_PAA_Point_Pos_Decimal() {
	SM_Physics::AABB aabb(SM_math::vec2(-10.0f, -10.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(-8.0f, -7.0f);

	return SM_Physics::Intersection_PointAndAABB(point, aabb);
}
bool SM_Tests::Test_PAA_AABB_Pos_Decimal() {
	SM_Physics::AABB aabb(SM_math::vec2(-10.0f, -10.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(4.0f, 7.0f);

	return SM_Physics::Intersection_PointAndAABB(point, aabb);
}