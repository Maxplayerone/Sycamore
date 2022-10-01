#include"IntersectionDetection.h"


bool SM_Physics::Intersection_LineAndPoint(SM_math::vec2& point, DebugDraw::DebugLine2D& line) {
	//getting the line equation for the line
	float dy = line.end.y - line.start.y;
	float dx = line.end.x - line.start.x;

	//we have a vertical line
	if (dx == 0) {
		return point.x == 0;
	}

	float a = dy / dx;

	float b = line.end.y - (a * line.end.x);

	//check if the point is in the line
	return (a * point.x + b) == point.y;
}

bool SM_Physics::Intersection_PointAndCircle(SM_math::vec2& point, Circle& circle) {
	//idk how the rb knows the center of the circle but ok
	SM_math::vec2 circleCenter = circle.rb.pos;
	SM_math::vec2 pointToCenter =  point - circleCenter;

	return pointToCenter.Lengthquared() < circle.radius * circle.radius;
}

bool SM_Physics::Intersection_PointAndAABB(SM_math::vec2& point, AABB& aabb) {
	return point.x > aabb.bottomLeft.x && point.x < aabb.topRight.x&& point.y > aabb.bottomLeft.y && point.y < aabb.topRight.y;
}

bool SM_Physics::Intersection_PointAndOBB(SM_math::vec2& point, Box2D& obb) {
	SM_math::vec2 pointRotated = SM_math::Rotate(point, obb.rb.rotation, obb.rb.pos);

	return pointRotated.x > obb.bottomLeft.x && pointRotated.x < obb.topRight.x&& pointRotated.y > obb.bottomLeft.y && pointRotated.y < obb.topRight.y;
}

bool SM_Physics::Intersection_LineAndCircle(DebugDraw::DebugLine2D& line, Circle& circle) {
	//if the end point or the start point is already in the circle
	if (Intersection_PointAndCircle(line.start, circle) || Intersection_PointAndCircle(line.end, circle)) return true;

	SM_math::vec2 vectorToCenter = circle.rb.pos - line.start;
	float scalingFactor = (vectorToCenter * line.end) / (vectorToCenter * vectorToCenter);
	SM_math::vec2 closestPointToCenter = line.start + (line.end * scalingFactor);
	return Intersection_PointAndCircle(closestPointToCenter, circle);
}