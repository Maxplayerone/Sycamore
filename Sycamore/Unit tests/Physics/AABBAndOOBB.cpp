#include"AABBAndOOBB.h"
#include"../Utils.h"

namespace SM_Tests {
	bool Test_AAO_Valid() {
		SM_Physics::AABB a(SM_math::vec2(4.0f, 3.0f), SM_math::vec2(6.0f, 6.0f));
		SM_Physics::Box2D b(SM_math::vec2(2.0f, 4.0f), SM_math::vec2(5.0f, 9.0f));

		return SM_Physics::Intersection_AABBAndOOBB(a, b);
	}
	bool Test_AAO_ValidIfRotated() {
		SM_Physics::AABB a(SM_math::vec2(4.0f, 3.0f), SM_math::vec2(6.0f, 6.0f));
		SM_Physics::Box2D b(SM_math::vec2(7.0f, 3.0f), SM_math::vec2(10.0f, 6.0f), 30.0f);

		//return SM_Physics::Intersection_AABBAndOOBB(a, b);
		return false;
	}
	bool Test_AAO_Invalid() {
		SM_Physics::AABB a(SM_math::vec2(4.0f, 3.0f), SM_math::vec2(6.0f, 6.0f));
		SM_Physics::Box2D b(SM_math::vec2(7.0f, 3.0f), SM_math::vec2(10.0f, 6.0f));

		return !SM_Physics::Intersection_AABBAndOOBB(a, b);
	}
}