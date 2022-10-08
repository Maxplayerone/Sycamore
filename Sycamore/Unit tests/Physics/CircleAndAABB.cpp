#include"CircleAndAABB.h"
#include"../Utils.h"

namespace SM_Tests {
	bool Test_CAA_Valid() {
		SM_Physics::Circle c(2, { 4.0f, 2.0f });
		SM_Physics::AABB aabb(SM_math::vec2( 2.0f, 3.0f), SM_math::vec2(5.0f, 6.0f));

		return SM_Physics::Intersection_CircleAndAABB(c, aabb);
	}
	bool Test_CAA_LengthTooShort() {
		SM_Physics::Circle c(2, { 4.0f, -2.0f });
		SM_Physics::AABB aabb(SM_math::vec2(2.0f, 3.0f), SM_math::vec2(5.0f, 6.0f));

		return !SM_Physics::Intersection_CircleAndAABB(c, aabb);
	}
	bool Test_CAA_CenterInAABB() {
		SM_Physics::Circle c(0.25f, { 3.0f, 4.0f });
		SM_Physics::AABB aabb(SM_math::vec2(2.0f, 3.0f), SM_math::vec2(5.0f, 6.0f));

		return SM_Physics::Intersection_CircleAndAABB(c, aabb);
	}
	bool Test_CAA_InvalidPosition() {
		SM_Physics::Circle c(2, { -4.0f, -2.0f });
		SM_Physics::AABB aabb(SM_math::vec2(2.0f, 3.0f), SM_math::vec2(5.0f, 6.0f));

		return !SM_Physics::Intersection_CircleAndAABB(c, aabb);
	}
}