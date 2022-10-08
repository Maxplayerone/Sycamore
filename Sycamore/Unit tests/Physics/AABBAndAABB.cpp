#include"AABBAndAABB.h"
#include"../Utils.h"

namespace SM_Tests {
	bool Test_AAA_Valid() {
		SM_Physics::AABB a1(SM_math::vec2( 4.0f, 3.0f), SM_math::vec2(6.0f, 6.0f ));
		SM_Physics::AABB a2(SM_math::vec2(2.0f, 4.0f), SM_math::vec2(5.0f, 9.0f));

		return SM_Physics::Intersection_AABBAndAABB(a1, a2);
	}

	bool Test_AAA_OneAxis() {
		SM_Physics::AABB a1(SM_math::vec2(4.0f, 3.0f), SM_math::vec2(6.0f, 6.0f));
		SM_Physics::AABB a2(SM_math::vec2(2.0f, -4.0f), SM_math::vec2(5.0f, 2.0f));

		return !SM_Physics::Intersection_AABBAndAABB(a1, a2);
	}
	bool Test_AAA_Invalid() {
		SM_Physics::AABB a1(SM_math::vec2(4.0f, 3.0f), SM_math::vec2(6.0f, 6.0f));
		SM_Physics::AABB a2(SM_math::vec2(10.0f, 3.0f), SM_math::vec2(16.0f, 6.0f));

		return !SM_Physics::Intersection_AABBAndAABB(a1, a2);
	}
	bool Test_AAA_OneAABBInAnotherOne() {
		SM_Physics::AABB a1(SM_math::vec2(4.0f, 3.0f), SM_math::vec2(7.0f, 6.0f));
		SM_Physics::AABB a2(SM_math::vec2(5.0f, 4.0f), SM_math::vec2(6.0f, 5.0f));

		return SM_Physics::Intersection_AABBAndAABB(a1, a2);
	}
}