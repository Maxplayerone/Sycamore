#pragma once
#include"../../Math/SM_math.h"
#include"../Rigidbody/Rigidbody.h"

namespace SM_Physics {
	struct Circle {
	private:
		float radius = 1.0f;
	public:
		Rigidbody rb = Rigidbody();

		Circle(float r, SM_math::vec2 center)
			: radius(r) {
			rb.SetPos(center);
		}


		Circle(SM_math::vec2 center)
			: radius(1.0f) {
			rb.SetPos(center);
		}

		void SetRadius(float length) { radius = length; }
		float GetRadius() { return radius; }
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

			rb.SetPos(SM_math::vec2(bottomLeft.x + boxDimensionsHalf.x, bottomLeft.y + boxDimensionsHalf.y));
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
			rb.SetRotation(0.0f);
		}


		Box2D(SM_math::vec2& bottomLeft, SM_math::vec2& topRight, float angle)
			:bottomLeft(bottomLeft), topRight(topRight) {
			diagonalLength = topRight - bottomLeft;
			halfLen = diagonalLength / 2;
			rb.SetRotation(angle);
		}

		SM_math::vec2& GetCenter() {
			return halfLen;
		}
	};
}

