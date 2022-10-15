#include"Collisions.h"

namespace SM_Physics {
	CollissionInfo& Collission_CircleAndCircle(Collider* a, Collider* b) {
        CollissionInfo result;
        float sumRadii = a->GetRadius() + b->GetRadius();
        SM_math::vec2 distance = b->GetPos() - a->GetPos();
        
        //the distance between the two points is bigger than their radii =
        // = the points don't collide
        if (distance.Lengthquared() > sumRadii * sumRadii) {
            result.hit = false;
            return result;
        }

        // Multiply by 0.5 because we want to separate each circle the same
        // amount. Consider updating to factor in the momentum and velocity
        
        float distLen = SM_math::Length(distance);
        float depth = SM_math::Abs(distLen - sumRadii) * 0.5f;
        SM_math::vec2 normal = SM_math::Normalize(distance, distLen);
        float distanceToPoint = a->GetRadius() - depth;
        SM_math::vec2 contactPoint = a->GetPos() + (normal * distanceToPoint);

        result.normal = normal;
        result.collissionDepth = depth;
        result.contactPoint[0] = contactPoint;
        result.contactPointsAmount = 1;
        result.hit = true;
        return result;
	}
}