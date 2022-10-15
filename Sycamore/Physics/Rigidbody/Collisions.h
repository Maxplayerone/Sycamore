#pragma once
#include"../../Math/SM_math.h"
#include"../Primitives/Primitives.h"

namespace SM_Physics {
	struct CollissionInfo {
		float collissionDepth = 0.0f; //how deep are the objects in themselves
		SM_math::vec2 contactPoint[4]; //exact point at which two points collide 
									//(the distance from the point to the object is exactly the same)
		uint contactPointsAmount = 0;
		SM_math::vec2 normal; //unit vector from the center of the first object
		bool hit = false;
	};

	CollissionInfo& Collission_CircleAndCircle(Collider* a,	Collider* b);
}
