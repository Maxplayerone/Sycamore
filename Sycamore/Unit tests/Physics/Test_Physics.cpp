#include"Tests_Physics.h"

#include"Test_Intersection_LineAndPoint.h"
#include"PointAndCircle.h"
#include"PointAndAABB.h"
#include"PointAndOOBB.h"

#include"../Utils.h"
#include<sstream>

void SM_Tests::T_Intersection_LineAndPoint() {
	HEADER("Tests intersection line and point");

	CHECK(Test_Valid);
	CHECK(Test_Point_Not_In_Line);
	CHECK(Test_Line_Is_Horizontal)
	CHECK(Test_Line_Is_Vertical);
	CHECK(Test_Point_On_Line_Start);
	CHECK(Test_Point_On_Negative_Coords);
}

void SM_Tests::T_Intersection_PointAndCircle() {
	HEADER("Tests intersection point and circle");

	CHECK(Test_PAC_Valid);
	CHECK(Test_PAC_Invalid);
	CHECK(Test_PAC_Point_In_Circle_Decimal_Pos);
	CHECK(Test_PAC_Point_Len_Bigger_Than_Radius);
}

void SM_Tests::T_Intersection_PointAndAABB() {
	HEADER("Tests intersection point and aabb");

	CHECK(Test_PAA_Valid);
	CHECK(Test_PAA_Invalid);
	CHECK(Test_PAA_Point_Pos_Decimal);
	CHECK(Test_PAA_AABB_Pos_Decimal);
}


void SM_Tests::T_Intersection_PointAndOOBB() {
	HEADER("Tests intersection point and oobb");
	
	CHECK(Test_PAO_Valid);
	CHECK(Test_PAO_Invalid);
	CHECK(Test_PAO_Point_Pos_Decimal);
	CHECK(Test_PAO_OOBB_Pos_Decimal);
	
}