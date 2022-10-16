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

// Box vertex and edge numbering:
//
//        ^ y
//        |
//        e1
//   v2 ------ v1
//    |        |
// e2 |        | e4  --> x
//    |        |
//   v3 ------ v4
//        e3

	enum Axis
	{
		FACE_A_X,
		FACE_A_Y,
		FACE_B_X,
		FACE_B_Y
	};

	enum EdgeNumbers
	{
		NO_EDGE = 0,
		EDGE1,
		EDGE2,
		EDGE3,
		EDGE4
	};
	
	union FeaturePair
	{
		struct Edges
		{
			char inEdge1;
			char outEdge1;
			char inEdge2;
			char outEdge2;
		} e;
		int value;
	};

	struct ClipVertex
	{
		ClipVertex() { fp.value = 0; }
		SM_math::vec2 v;
		FeaturePair fp;
	};
	
	void Flip(FeaturePair& fp)
	{
		SM_math::Swap(fp.e.inEdge1, fp.e.inEdge2);
		SM_math::Swap(fp.e.outEdge1, fp.e.outEdge2);
	}
	
	int ClipSegmentToLine(ClipVertex vOut[2], ClipVertex vIn[2],
		const SM_math::vec2& normal, float offset, char clipEdge)
	{
		// Start with no output points
		int numOut = 0;

		// Calculate the distance of end points to the line
		float distance0 = Dot(normal, vIn[0].v) - offset;
		float distance1 = Dot(normal, vIn[1].v) - offset;

		// If the points are behind the plane
		if (distance0 <= 0.0f) vOut[numOut++] = vIn[0];
		if (distance1 <= 0.0f) vOut[numOut++] = vIn[1];

		// If the points are on different sides of the plane
		if (distance0 * distance1 < 0.0f)
		{
			// Find intersection point of edge and plane
			float interp = distance0 / (distance0 - distance1);
			vOut[numOut].v = vIn[0].v + interp * (vIn[1].v - vIn[0].v);
			if (distance0 > 0.0f)
			{
				vOut[numOut].fp = vIn[0].fp;
				vOut[numOut].fp.e.inEdge1 = clipEdge;
				vOut[numOut].fp.e.inEdge2 = NO_EDGE;
			}
			else
			{
				vOut[numOut].fp = vIn[1].fp;
				vOut[numOut].fp.e.outEdge1 = clipEdge;
				vOut[numOut].fp.e.outEdge2 = NO_EDGE;
			}
			++numOut;
		}

		return numOut;
	}
	
	static void ComputeIncidentEdge(ClipVertex c[2], const SM_math::vec2& h, const SM_math::vec2& pos,
		const SM_math::mat2& Rot, const SM_math::vec2& normal)
	{
		// The normal is from the reference box. Convert it
		// to the incident boxe's frame and flip sign.
		SM_math::mat2 RotT = Rot.Transpose();
		SM_math::vec2 n = (RotT * normal) * -1.0f;
		SM_math::vec2 nAbs = Abs(n);

		if (nAbs.x > nAbs.y)
		{
			if (SM_math::Sign(n.x) > 0.0f)
			{
				c[0].v.Set(h.x, -h.y);
				c[0].fp.e.inEdge2 = EDGE3;
				c[0].fp.e.outEdge2 = EDGE4;

				c[1].v.Set(h.x, h.y);
				c[1].fp.e.inEdge2 = EDGE4;
				c[1].fp.e.outEdge2 = EDGE1;
			}
			else
			{
				c[0].v.Set(-h.x, h.y);
				c[0].fp.e.inEdge2 = EDGE1;
				c[0].fp.e.outEdge2 = EDGE2;

				c[1].v.Set(-h.x, -h.y);
				c[1].fp.e.inEdge2 = EDGE2;
				c[1].fp.e.outEdge2 = EDGE3;
			}
		}
		else
		{
			if (SM_math::Sign(n.y) > 0.0f)
			{
				c[0].v.Set(h.x, h.y);
				c[0].fp.e.inEdge2 = EDGE4;
				c[0].fp.e.outEdge2 = EDGE1;

				c[1].v.Set(-h.x, h.y);
				c[1].fp.e.inEdge2 = EDGE1;
				c[1].fp.e.outEdge2 = EDGE2;
			}
			else
			{
				c[0].v.Set(-h.x, -h.y);
				c[0].fp.e.inEdge2 = EDGE2;
				c[0].fp.e.outEdge2 = EDGE3;

				c[1].v.Set(h.x, -h.y);
				c[1].fp.e.inEdge2 = EDGE3;
				c[1].fp.e.outEdge2 = EDGE4;
			}
		}

		c[0].v = pos + Rot * c[0].v;
		c[1].v = pos + Rot * c[1].v;
	}
	
	// The normal points from A to B
	CollissionInfo& Collission_BoxAndBox(Box2D* a, Box2D* b)
	{
		// Setup
		SM_math::vec2 halfA = 0.5f * a->GetRadius();
		SM_math::vec2 halfB = 0.5f * b->GetRadius();

		SM_math::vec2 posA = a->GetPos();
		SM_math::vec2 posB = b->GetPos();

		SM_math::mat2 rotMatA(a->GetAngle());
		SM_math::mat2 rotMatB(b->GetAngle());

		SM_math::mat2 rotMatAT = rotMatA.Transpose();
		SM_math::mat2 rotMatBT = rotMatB.Transpose();

		SM_math::vec2 dp = posB - posA;
		//dp rotated in a local space
		SM_math::vec2 dA = rotMatAT * dp;
		//dp rotated in b local space
		SM_math::vec2 dB = rotMatAT * dp;

		//matrix rotating from b local space to a local space
		SM_math::mat2 C = rotMatAT * rotMatB;
		SM_math::mat2 absC = Abs(C);
		//matrix rotating from a local space to b local space
		SM_math::mat2 absCT = absC.Transpose();


		//Separating axis theorem
		// Box A faces
		SM_math::vec2 faceA = Abs(dA) - halfA - absC * halfB;
		if (faceA.x > 0.0f || faceA.y > 0.0f) {
			CollissionInfo info;
			info.hit = false;
			return info;
		}

		// Box B faces
		SM_math::vec2 faceB = Abs(dB) - absCT * halfA - halfB;
		if (faceB.x > 0.0f || faceB.y > 0.0f) {
			CollissionInfo info;
			info.hit = false;
			return info;
		}

		// Find best axis
		Axis axis;
		float separation;
		SM_math::vec2 normal;

		// Box A faces
		axis = FACE_A_X;
		separation = faceA.x;
		normal = dA.x > 0.0f ? rotMatA.column1 : rotMatA.column1 * -1.0f;

		const float relativeTol = 0.95f;
		const float absoluteTol = 0.01f;

		if (faceA.y > relativeTol * separation + absoluteTol * halfA.y)
		{
			axis = FACE_A_Y;
			separation = faceA.y;
			normal = dA.y > 0.0f ? rotMatA.column2 : rotMatA.column2 * -1.0f;
		}

		// Box B faces
		if (faceB.x > relativeTol * separation + absoluteTol * halfB.x)
		{
			axis = FACE_B_X;
			separation = faceB.x;
			normal = dB.x > 0.0f ? rotMatB.column1 : rotMatB.column1 * -1.0f;
		}

		if (faceB.y > relativeTol * separation + absoluteTol * halfB.y)
		{
			axis = FACE_B_Y;
			separation = faceB.y;
			normal = dB.y > 0.0f ? rotMatB.column2 : rotMatB.column2 * 1.0f;
		}


		// Setup clipping plane data based on the separating axis
		SM_math::vec2 frontNormal, sideNormal;
		ClipVertex incidentEdge[2];
		float front, negSide, posSide;
		char negEdge, posEdge;

		// Compute the clipping lines and the line segment to be clipped.
		switch (axis)
		{
		case FACE_A_X:
		{
			frontNormal = normal;
			front = Dot(posA, frontNormal) + halfA.x;
			sideNormal = rotMatA.column2;
			float side = Dot(posA, sideNormal);
			negSide = -side + halfA.y;
			posSide = side + halfA.y;
			negEdge = EDGE3;
			posEdge = EDGE1;
			ComputeIncidentEdge(incidentEdge, halfB, posB, rotMatB, frontNormal);
		}
		break;

		case FACE_A_Y:
		{
			frontNormal = normal;
			front = Dot(posA, frontNormal) + halfA.y;
			sideNormal = rotMatA.column1;
			float side = Dot(posA, sideNormal);
			negSide = -side + halfA.x;
			posSide = side + halfA.x;
			negEdge = EDGE2;
			posEdge = EDGE4;
			ComputeIncidentEdge(incidentEdge, halfB, posB, rotMatB, frontNormal);
		}
		break;

		case FACE_B_X:
		{
			frontNormal = normal * -1.0f;
			front = Dot(posB, frontNormal) + halfB.x;
			sideNormal = rotMatB.column2;
			float side = Dot(posB, sideNormal);
			negSide = -side + halfB.y;
			posSide = side + halfB.y;
			negEdge = EDGE3;
			posEdge = EDGE1;
			ComputeIncidentEdge(incidentEdge, halfA, posA, rotMatA, frontNormal);
		}
		break;

		case FACE_B_Y:
		{
			frontNormal = normal * -1.0f;
			front = Dot(posB, frontNormal) + halfB.y;
			sideNormal = rotMatB.column1;
			float side = Dot(posB, sideNormal);
			negSide = -side + halfB.x;
			posSide = side + halfB.x;
			negEdge = EDGE2;
			posEdge = EDGE4;
			ComputeIncidentEdge(incidentEdge, halfA, posA, rotMatA, frontNormal);
		}
		break;
		}

		// clip other face with 5 box planes (1 face plane, 4 edge planes)

		ClipVertex clipPoints1[2];
		ClipVertex clipPoints2[2];
		int np;

		// Clip to box side 1
		np = ClipSegmentToLine(clipPoints1, incidentEdge, sideNormal *  -1.0f, negSide, negEdge);

		if (np < 2) {
			CollissionInfo info;
			info.hit = false;
			return info;
		}
		// Clip to negative box side 1
		np = ClipSegmentToLine(clipPoints2, clipPoints1, sideNormal, posSide, posEdge);

		if (np < 2) {
			CollissionInfo info;
			info.hit = false;
			return info;
		}
		// Now clipPoints2 contains the clipping points.
		// Due to roundoff, it is possible that clipping removes all points.

		int numContacts = 0;
		CollissionInfo info;
		for (int i = 0; i < 2; ++i)
		{
			float separation = Dot(frontNormal, clipPoints2[i].v) - front;

			if (separation <= 0)
			{
				/*
				contacts[numContacts].separation = separation;
				contacts[numContacts].normal = normal;
				// slide contact point onto reference face (easy to cull)
				contacts[numContacts].position = clipPoints2[i].v - separation * frontNormal;
				contacts[numContacts].feature = clipPoints2[i].fp;
				if (axis == FACE_B_X || axis == FACE_B_Y)
					Flip(contacts[numContacts].feature);
				++numContacts;
				*/
				info.collissionDepth = separation;
				info.hit = true;
				info.normal = normal;
			}
		}
		info.contactPointsAmount = numContacts;
		return info;
	}
	
}