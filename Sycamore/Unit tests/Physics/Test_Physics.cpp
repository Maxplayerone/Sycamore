#include"Tests_Physics.h"

#include"Test_Intersection_LineAndPoint.h"
#include"PointAndCircle.h"
#include"PointAndAABB.h"
#include"PointAndOOBB.h"

#include"LineAndCircle.h"
#include"LineAndAABB.h"
#include"lineAndOOBB.h"

#include"CircleAndCircle.h"
#include"CircleAndAABB.h"

#include"AABBAndAABB.h"
#include"AABBAndOOBB.h"

#include"../Utils.h"

namespace SM_Tests {
	void T_Intersection_LineAndPoint() {
		HEADER("Tests intersection line and point");

		CHECK(Test_Valid);
		CHECK(Test_Point_Not_In_Line);
		CHECK(Test_Line_Is_Horizontal)
		CHECK(Test_Line_Is_Vertical);
		CHECK(Test_Point_On_Line_Start);
		CHECK(Test_Point_On_Negative_Coords);
	}

	void T_Intersection_PointAndCircle() {
		HEADER("Tests intersection point and circle");

		CHECK(Test_PAC_Valid);
		CHECK(Test_PAC_Invalid);
		CHECK(Test_PAC_Point_In_Circle_Decimal_Pos);
		CHECK(Test_PAC_Point_Len_Bigger_Than_Radius);
	}

	void T_Intersection_PointAndAABB() {
		HEADER("Tests intersection point and aabb");

		CHECK(Test_PAA_Valid);
		CHECK(Test_PAA_Invalid);
		CHECK(Test_PAA_Point_Pos_Decimal);
		CHECK(Test_PAA_AABB_Pos_Decimal);
	}


	void T_Intersection_PointAndOOBB() {
		HEADER("Tests intersection point and oobb");

		CHECK(Test_PAO_Valid);
		CHECK(Test_PAO_Invalid);
		CHECK(Test_PAO_Point_Pos_Decimal);
		CHECK(Test_PAO_OOBB_Pos_Decimal);
		CHECK(Test_PAO_Rotated_Valid);
		CHECK(Test_PAO_Rotated_Invalid);

	}

	void T_Intersection_LineAndCircle() {
		HEADER("Tests intersection line and circle");

		CHECK(Test_LAC_Valid);
		CHECK(Test_LAC_Invalid);
		CHECK(Test_LAC_Start_In_Circle);
		CHECK(Test_LAC_Vertical_Line);
		CHECK(Test_LAC_Horizontal_Line);
	}

	void T_Intersection_LineAndAABB() {
		HEADER("Tests intersection line and aabb");

		CHECK(Test_LAA_Valid);
		CHECK(Test_LAA_Invalid);
		CHECK(Test_LAA_Starting_In_AABB);
		CHECK(Test_LAA_Line_Too_Short);
		CHECK(Test_LAA_Line_With_Zero_Coords);
	}

	void T_Intersection_LineAndOOBB() {
		HEADER("Tests intersection line and oobb");

		CHECK(Test_LAO_Valid);
		CHECK(Test_LAO_Invalid);
		CHECK(Test_LAO_Line_Too_Short);
		CHECK(Test_LAO_Line_With_Zero_Coords);
		CHECK(Test_LAO_Starting_In_OOBB);
		CHECK(Test_LAO_Rotated_Valid);
		CHECK(Test_LAO_Rotated_Invalid);
	}

	void T_Intersection_CircleAndCircle() {
		HEADER("Intersection circle and circle");

		CHECK(Test_CAC_Valid);
		CHECK(Test_CAC_Valid_Same_Data_Swapped_Position_Calculation);
		CHECK(Test_CAC_Invalid);
	}

	void T_Intersection_CircleAndAABB() {
		HEADER("Intersection circle and aabb");

		CHECK(Test_CAA_Valid);
		CHECK(Test_CAA_LengthTooShort);
		CHECK(Test_CAA_CenterInAABB);
		CHECK(Test_CAA_InvalidPosition);
	}

	void T_Intersection_AABBAndAABB() {
		HEADER("intersection aabb and aabb");

		CHECK(Test_AAA_Valid);
		CHECK(Test_AAA_Invalid);
		CHECK(Test_AAA_OneAABBInAnotherOne);
		CHECK(Test_AAA_OneAxis);
	}

	void T_Intersection_AABBAndOOBB() {
		HEADER("intersection aabb and oobb");

		CHECK(Test_AAO_Valid);
		CHECK(Test_AAO_ValidIfRotated);
		CHECK(Test_AAO_Invalid);
	}
}