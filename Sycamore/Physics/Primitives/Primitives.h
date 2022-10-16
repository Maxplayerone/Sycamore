#pragma once
#include"../../Math/SM_math.h"

namespace SM_Physics {
	struct Collider {
	public:
		virtual void SetPosition(SM_math::vec2& _pos) = 0;
		virtual SM_math::vec2& GetPos() = 0;

		virtual float GetRadius() = 0;
	};

	struct Circle : public Collider {
	private:
		float radius = 1.0f;
		//the circle only gets position from the rigidbody
		SM_math::vec2 pos;
	public:

		Circle(float r)
			: radius(r) {
			pos = SM_math::vec2(0.0f, 0.0f);
		}
		void SetRadius(float length) { radius = length; }
		float GetRadius() override{  return radius; }

		void SetPosition(SM_math::vec2& _pos) override {
			pos = _pos;
		}

		SM_math::vec2& GetPos() override {
			return pos;
		}
	};

	
	struct AABB : Collider{
		//honestly I have no ided what this is used for
		/*
		SM_math::vec2 diagonalLength = { 1.0f, 1.0f };
		SM_math::vec2 boxDimensionsHalf = { 0.5f, 0.5f };

		SM_math::vec2 bottomLeft = SM_math::vec2(1.0f);
		SM_math::vec2 topRight = SM_math::vec2(1.0f);
		*/
	private:
		float radius = 0.0f;
		SM_math::vec2 pos;
	public:
		/*
		AABB(SM_math::vec2& bottomLeft, SM_math::vec2& topRight)
			:bottomLeft(bottomLeft), topRight(topRight) {
			diagonalLength = topRight - bottomLeft;
			boxDimensionsHalf = diagonalLength / 2;
		}
		*/
		AABB(float r) {
			radius = r;
		}

		float GetRadius() override { return radius; }

		void SetPosition(SM_math::vec2& _pos) override {
			pos = _pos;
		}

		SM_math::vec2& GetPos() override {
			return pos;
		}
	};
	
	struct Box2D : Collider {
		/*
		SM_math::vec2 diagonalLength = { 1.0f, 1.0f };
		SM_math::vec2 halfLen = { 0.5f, 0.5f };

		SM_math::vec2 bottomLeft = SM_math::vec2(1.0f);
		SM_math::vec2 topRight = SM_math::vec2(1.0f);

		Box2D(SM_math::vec2& bottomLeft, SM_math::vec2& topRight)
			:bottomLeft(bottomLeft), topRight(topRight) {
			diagonalLength = topRight - bottomLeft;
			halfLen = diagonalLength / 2;
		}


		Box2D(SM_math::vec2& bottomLeft, SM_math::vec2& topRight, float angle)
			:bottomLeft(bottomLeft), topRight(topRight) {
			diagonalLength = topRight - bottomLeft;
			halfLen = diagonalLength / 2;
		}

		SM_math::vec2& GetCenter() {
			return halfLen;
		}
		*/
	private:
		float radius = 0.0f;
		SM_math::vec2 pos;
		float angle;
	public:
		Box2D(float r, float _angle) {
			radius = r;
			angle = _angle;
		}

		float GetRadius() override { return radius; }

		void SetPosition(SM_math::vec2& _pos) override {
			pos = _pos;
		}

		SM_math::vec2& GetPos() override {
			return pos;
		}

		float GetAngle() { return angle; }
	};
	
	
}
