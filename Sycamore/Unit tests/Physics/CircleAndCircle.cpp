#include"CircleAndCircle.h"
#include"../Utils.h"

namespace SM_Tests {
	bool Test_CAC_Valid() {
		SM_Physics::Circle c1(2, {1.0f, 4.0f});
		SM_Physics::Circle c2(2, { 4.0f, 6.0f });

		return SM_Physics::Intersection_CircleAndCircle(c1, c2);
	}
	bool Test_CAC_Valid_Same_Data_Swapped_Position_Calculation() {
		SM_Physics::Circle c1(2, { 1.0f, 4.0f });
		SM_Physics::Circle c2(2, { 4.0f, 6.0f });

		return SM_Physics::Intersection_CircleAndCircle(c2, c1);
	}
	bool Test_CAC_Invalid() {
		SM_Physics::Circle c1(1, { 1.0f, 4.0f });
		SM_Physics::Circle c2(1, { 4.0f, 6.0f });

		return !SM_Physics::Intersection_CircleAndCircle(c1, c2);
	}
}