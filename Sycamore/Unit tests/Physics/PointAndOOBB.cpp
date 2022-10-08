#include"PointAndOOBB.h"
#include"../Utils.h"

bool SM_Tests::Test_PAO_Valid() {
	SM_Physics::Box2D box2D(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(4.0f, 7.0f);

	return SM_Physics::Intersection_PointAndOBB(point, box2D);
}
bool SM_Tests::Test_PAO_Invalid() {
	SM_Physics::Box2D box2D(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(-4.0f, 7.0f);

	return !SM_Physics::Intersection_PointAndOBB(point, box2D);
}
bool SM_Tests::Test_PAO_Point_Pos_Decimal() {
	SM_Physics::Box2D box2D(SM_math::vec2(-10.0f, -10.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(-8.0f, -7.0f);

	return SM_Physics::Intersection_PointAndOBB(point, box2D);
}
bool SM_Tests::Test_PAO_OOBB_Pos_Decimal() {
	SM_Physics::Box2D box2D(SM_math::vec2(-10.0f, -10.0f), SM_math::vec2(10.0f, 10.0f));
	SM_math::vec2 point(8.0f, 7.0f);

	return SM_Physics::Intersection_PointAndOBB(point, box2D);
}

bool SM_Tests::Test_PAO_Rotated_Valid() {
	SM_Physics::Box2D box2D(SM_math::vec2(-10.0f, -10.0f), SM_math::vec2(10.0f, 10.0f));
	box2D.rb.SetRotation(45.0f);
	SM_math::vec2 point(8.0f, 7.0f);

	return SM_Physics::Intersection_PointAndOBB(point, box2D);
}
bool SM_Tests::Test_PAO_Rotated_Invalid() {
	SM_Physics::Box2D box2D(SM_math::vec2(0.0f, 0.0f), SM_math::vec2(10.0f, 10.0f));
	box2D.rb.SetRotation(45.0f);
	SM_math::vec2 point(8.0f, -7.0f);

	return !SM_Physics::Intersection_PointAndOBB(point, box2D);
}