#include"PointAndCircle.h"
#include"../Utils.h"

bool SM_Tests::Test_PAC_Valid() {
	SM_Physics::Circle circle(2.0f, { 3.0f, 5.0f });
	SM_math::vec2 point(4.0f, 5.0f);

	return SM_Physics::Intersection_PointAndCircle(point, circle);
}
bool SM_Tests::Test_PAC_Invalid() {
	SM_Physics::Circle circle(2.0f, { 3.0f, 5.0f });
	SM_math::vec2 point(10.0f, -25.0f);

	return !SM_Physics::Intersection_PointAndCircle(point, circle);
}
bool SM_Tests::Test_PAC_Point_Len_Bigger_Than_Radius() {
	SM_Physics::Circle circle(2.0f, { 3.0f, 5.0f });
	SM_math::vec2 point(10.0f, 5.0f);

	return !SM_Physics::Intersection_PointAndCircle(point, circle);
}
bool SM_Tests::Test_PAC_Point_In_Circle_Decimal_Pos() {
	SM_Physics::Circle circle(10.0f, { 1.0f, 3.0f });
	SM_math::vec2 point(-1.0f, -3.0f);

	return SM_Physics::Intersection_PointAndCircle(point, circle);
}