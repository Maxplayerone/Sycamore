#include"IntersectionDetection.h"

float MaxValue(float a, float b) {
	return (a > b) ? a : b;
}

float MinValue(float a, float b) {
	return (a < b) ? a : b;
}

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
	SM_math::vec2 circleCenter = circle.rb->GetPos();
	SM_math::vec2 pointToCenter =  point - circleCenter;

	return pointToCenter.Lengthquared() < circle.GetRadius() * circle.GetRadius();
}

bool SM_Physics::Intersection_PointAndAABB(SM_math::vec2& point, AABB& aabb) {
	return point.x > aabb.bottomLeft.x && point.x < aabb.topRight.x&& point.y > aabb.bottomLeft.y && point.y < aabb.topRight.y;
}

bool SM_Physics::Intersection_PointAndOBB(SM_math::vec2& point, Box2D& obb) {
	SM_math::vec2 pointRotated = SM_math::Rotate(point, obb.rb.GetRotation(), obb.rb.GetPos());

	return pointRotated.x > obb.bottomLeft.x && pointRotated.x < obb.topRight.x&& pointRotated.y > obb.bottomLeft.y && pointRotated.y < obb.topRight.y;
}

bool SM_Physics::Intersection_LineAndCircle(DebugDraw::DebugLine2D& line, Circle& circle) {
	//if the end point or the start point is already in the circle
	if (Intersection_PointAndCircle(line.start, circle) || Intersection_PointAndCircle(line.end, circle)) return true;

	SM_math::vec2 vectorToCenter = circle.rb->GetPos() - line.start;
	float scalingFactor = (vectorToCenter * line.end) / (vectorToCenter * vectorToCenter);
	SM_math::vec2 closestPointToCenter = line.start + (line.end * scalingFactor);
	return Intersection_PointAndCircle(closestPointToCenter, circle);
}

bool SM_Physics::Intersection_LineAndAABB(DebugDraw::DebugLine2D& line, AABB& aabb) {
	//if one of the poins is already in aabb
	if (Intersection_PointAndAABB(line.start, aabb) || Intersection_PointAndAABB(line.end, aabb))
		return true;

	SM_math::vec2 lineUnit = SM_math::vec2(line.end.x - line.start.x, line.end.y - line.start.y);
	lineUnit.Normalize();
	//if one of the coords were zero than x or y is still zero now
	//we will multiply by 1 / lineUnit instead of dividing by lineUint
	//to catch DivisionByZero errors
	lineUnit.x = (lineUnit.x != 0) ? 1 / lineUnit.x : 0.0f;
	lineUnit.y = (lineUnit.y != 0) ? 1 / lineUnit.y : 0.0f;

	//vector from the line line start to the bottomLeft corner of the aabb
	SM_math::vec2 min = aabb.bottomLeft - line.start;
	min = SM_math::vec2(min.x * lineUnit.x, min.y * lineUnit.y);

	//vector from the line start to the topRight corner of the aabb
	SM_math::vec2 max = aabb.topRight - line.start;
	max = SM_math::vec2(max.x * lineUnit.x, max.y * lineUnit.y);

	//idk what these are for to be honest
	float t_min = MaxValue(MinValue(min.x, max.x), MinValue(min.y, max.y));
	float t_max = MinValue(MaxValue(min.x, max.x), MaxValue(min.y, max.y));

	if (t_max < 0 || t_min > t_max)
		return false;

	float t = (t_min < 0.0f) ? t_max : t_min;
	return t > 0.0f && t * t < line.LengthSquared();
}

bool SM_Physics::Intersection_LineAndOOBB(DebugDraw::DebugLine2D& line, Box2D& oobb) {
	float rotationAngle = -oobb.rb.GetRotation();
	SM_math::vec2 center = oobb.GetCenter();

	SM_math::vec2 localLineStart = line.start;
	SM_math::vec2 localLineEnd = line.end;
	localLineStart = SM_math::Rotate(localLineStart, rotationAngle, center);
	localLineEnd = SM_math::Rotate(localLineEnd, rotationAngle, center);

	DebugDraw::DebugLine2D localLine;
	localLine.start = localLineStart;
	localLine.end = localLineEnd;

	SM_Physics::AABB aabb(oobb.bottomLeft, oobb.topRight);
	return Intersection_LineAndAABB(localLine, aabb);
}

bool SM_Physics::Intersection_CircleAndCircle(Circle& c1, Circle& c2) {
	//there is no difference which circle pos is first because the difference is a negative sign
	//which we get rid of while squaring the distance
	float distFromCenters = (c2.rb->GetPos() - c1.rb->GetPos()).Lengthquared();
	float sumOfRadiuses = (c2.GetRadius() + c1.GetRadius()) * (c2.GetRadius() + c1.GetRadius());

	return sumOfRadiuses >= distFromCenters;
}

bool SM_Physics::Intersection_CircleAndAABB(Circle& circle, AABB& aabb) {
	SM_math::vec2 closest = circle.rb->GetPos();
	SM_math::vec2 min = aabb.bottomLeft;
	SM_math::vec2 max = aabb.topRight;

	if (closest.x < min.x) {
		closest.x = min.x;
	}
	else if (closest.x > max.x) {
		closest.x = max.x;
	}

	if (closest.y < min.y) {
		closest.y = min.y;
	}
	else if (closest.y > max.y) {
		closest.y = max.y;
	}

	SM_math::vec2 boxToCircle = closest - circle.rb->GetPos();
	return boxToCircle.Lengthquared() <= circle.GetRadius() * circle.GetRadius();

}

struct interval {
	float min;
	float max;
};

interval& GetInterval(SM_Physics::AABB& aabb, SM_math::vec2 axis) {
	interval result = { FLT_MAX, FLT_MIN};
	
	SM_math::vec2 min = aabb.bottomLeft;
	SM_math::vec2 max = aabb.topRight;

	SM_math::vec2 points[4] = {
		min, SM_math::vec2(min.x, max.y),
		SM_math::vec2(max.x, min.y), max
	};

	for (auto point : points) {
		float projection = point * axis;
		if (projection < result.min)
			result.min = projection;
		if (projection > result.max)
			result.max = projection;
	}

	return result;

}

interval& GetInterval(SM_Physics::Box2D& box, SM_math::vec2 axis) {
	interval result = { FLT_MAX, FLT_MIN };

	SM_math::vec2 min = box.bottomLeft;
	SM_math::vec2 max = box.topRight;

	SM_math::vec2 points[4] = {
		min, SM_math::vec2(min.x, max.y),
		SM_math::vec2(max.x, min.y), max
	};

	if (box.rb.GetRotation() != 0.0f) {
		for (int i = 0; i < 4; i++) {
			points[i] = SM_math::Rotate(points[i], box.rb.GetRotation(), box.rb.GetPos());
		}
	}

	for (auto point : points) {
		float projection = point * axis;
		if (projection < result.min)
			result.min = projection;
		if (projection > result.max)
			result.max = projection;
	}

	return result;

}

bool OverlapOnAxis(SM_Physics::AABB& a1, SM_Physics::AABB& a2, SM_math::vec2 axis) {
	interval result1 = GetInterval(a1, axis);
	interval result2 = GetInterval(a2, axis);

	return result2.max > result1.min && result1.max > result2.min;
}

bool OverlapOnAxis(SM_Physics::AABB& a1, SM_Physics::Box2D& a2, SM_math::vec2 axis) {
	interval result1 = GetInterval(a1, axis);
	interval result2 = GetInterval(a2, axis);

	return result2.max > result1.min && result1.max > result2.min;
}


bool SM_Physics::Intersection_AABBAndAABB(AABB& b1, AABB& b2) {
	bool r1 = OverlapOnAxis(b1, b2, SM_math::vec2(1.0f, 0.0f));
	bool r2 = OverlapOnAxis(b1, b2, SM_math::vec2(0.0f, 1.0f));

	return r1 == true && r2 == true;
}

bool SM_Physics::Intersection_AABBAndOOBB(AABB& b1, Box2D& b2) {
	bool r1 = OverlapOnAxis(b1, b2, SM_math::vec2(1.0f, 0.0f));
	bool r2 = OverlapOnAxis(b1, b2, SM_math::vec2(0.0f, 1.0f));

	return r1 == true && r2 == true;
}

