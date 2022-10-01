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
}