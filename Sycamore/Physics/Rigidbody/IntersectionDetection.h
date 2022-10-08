#pragma once
#include"../../Math/SM_math.h"

#include"../../src/Rendering/DebugDraw.h"

#include"../Primitives/Primitives.h"

namespace SM_Physics {	
	bool Intersection_PointAndCircle(SM_math::vec2& point, Circle& circle);
	bool Intersection_PointAndAABB(SM_math::vec2& point, AABB& aabb);
	bool Intersection_PointAndOBB(SM_math::vec2& point, Box2D& obb);

	bool Intersection_LineAndPoint(SM_math::vec2& point, DebugDraw::DebugLine2D& line);
	bool Intersection_LineAndCircle(DebugDraw::DebugLine2D& line, Circle& circle);
	bool Intersection_LineAndAABB(DebugDraw::DebugLine2D& line, AABB& aabb);
	bool Intersection_LineAndOOBB(DebugDraw::DebugLine2D& line, Box2D& oobb);

	bool Intersection_CircleAndCircle(Circle& c1, Circle& c2);
	bool Intersection_CircleAndAABB(Circle& circle, AABB& aabb);
	//intersection circleAndAABB

	bool Intersection_AABBAndAABB(AABB& b1, AABB& b2);
	bool Intersection_AABBAndOOBB(AABB& b1, Box2D& b2);
}