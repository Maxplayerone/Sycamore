#include"Master.h"
#include"Physics/Tests_Physics.h"

#include"Utils.h"

void SM_Tests::Init() {
	LOGGER_INFO("==========================================================");
	T_Intersection_LineAndPoint();
	T_Intersection_PointAndCircle();
	T_Intersection_PointAndAABB();
	LOGGER_INFO("============================================================");

}