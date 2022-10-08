#include"Master.h"
#include"Physics/Tests_Physics.h"

#include"Utils.h"

void SM_Tests::Init() {
	LOGGER_INFO("==========================================================");
	T_Intersection_LineAndPoint();
	T_Intersection_PointAndCircle();
	T_Intersection_PointAndAABB();
	T_Intersection_PointAndOOBB();
	T_Intersection_LineAndCircle();
	T_Intersection_LineAndAABB();
	T_Intersection_LineAndOOBB();
	T_Intersection_CircleAndCircle();
	T_Intersection_CircleAndAABB();
	T_Intersection_AABBAndAABB();
	T_Intersection_AABBAndOOBB();
	LOGGER_INFO("============================================================");

}