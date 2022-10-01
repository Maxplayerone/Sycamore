#pragma once
#include"../../Math/SM_math.h"
#include"../Rigidbody/Rigidbody.h"

namespace SM_Physics {
	struct Circle {
		float radius = 1.0f;
		Rigidbody rb = Rigidbody();

		Circle(float r, SM_math::vec2 center)
			: radius(r) {
			rb.pos = center;
		}


		Circle(SM_math::vec2 center)
			: radius(1.0f) {
			rb.pos = center;
		}
	};

	struct AABB {
		//honestly I have no ided what this is used for
		SM_math::vec2 diagonalLength = { 1.0f, 1.0f };
		SM_math::vec2 boxDimensionsHalf = { 0.5f, 0.5f };

		SM_math::vec2 bottomLeft = SM_math::vec2(1.0f);
		SM_math::vec2 topRight = SM_math::vec2(1.0f);

		Rigidbody rb = Rigidbody();

		AABB(SM_math::vec2& bottomLeft, SM_math::vec2& topRight)
			:bottomLeft(bottomLeft), topRight(topRight) {
			diagonalLength = topRight - bottomLeft;
			boxDimensionsHalf = diagonalLength / 2;

			rb.pos = SM_math::vec2(bottomLeft.x + boxDimensionsHalf.x, bottomLeft.y + boxDimensionsHalf.y);
		}
	};

	struct Box2D {
		SM_math::vec2 diagonalLength = { 1.0f, 1.0f };
		SM_math::vec2 halfLen = { 0.5f, 0.5f };

		SM_math::vec2 bottomLeft = SM_math::vec2(1.0f);
		SM_math::vec2 topRight = SM_math::vec2(1.0f);

		Rigidbody rb = Rigidbody();


		Box2D(SM_math::vec2& bottomLeft, SM_math::vec2& topRight)
			:bottomLeft(bottomLeft), topRight(topRight) {
			diagonalLength = topRight - bottomLeft;
			halfLen = diagonalLength / 2;
		}


		Box2D(SM_math::vec2& bottomLeft, SM_math::vec2& topRight, float angle)
			:bottomLeft(bottomLeft), topRight(topRight) {
			diagonalLength = topRight - bottomLeft;
			halfLen = diagonalLength / 2;
			rb.rotation = angle;
		}
	};
}

