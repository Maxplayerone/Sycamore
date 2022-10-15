#pragma once
#include"../../Math/SM_math.h"
#include"../../src/ECS/Transform.h"
#include"../Primitives/Primitives.h"

namespace SM_Physics {

	class Rigidbody {
	private:
		SM_math::vec2 pos = SM_math::vec2(0.0f, 0.0f);
		float rotation = 0.0f;
		Collider* collider;


		SM_math::vec2 m_forceAccum;
		SM_math::vec2 m_velocity = SM_math::vec2(0.0f, 0.0f);
		Transform* m_renderingTrans = nullptr;

		float m_mass = 0.0f;
		float m_inverseMass = 0.0f;
		//aka the bouncyness level
		//0.0f is no bouncyness
		//1.0f is max bouncyness
		float cor = 1.0f;

		void ClearAccum();
		void SyncWithRenderingPos();
	public:
		Rigidbody() :
			pos(SM_math::vec2(0.0f)), rotation(0.0f) {
			m_forceAccum = SM_math::vec2(0.0f, 0.0f);
		}

		Rigidbody(float angle) :
			pos(SM_math::vec2(0.0f)), rotation(angle) {
			m_forceAccum = SM_math::vec2(0.0f, 0.0f);
		}

		Rigidbody(SM_math::vec2& pos):
			pos(pos), rotation(0.0f) {
			m_forceAccum = SM_math::vec2(0.0f, 0.0f);
		}

		SM_math::vec2& GetPos() { return pos; }
		float GetRotation() { return rotation; }

		void SetPos(SM_math::vec2& _pos) { pos = _pos; }
		void SetRotation(float angle) { rotation = angle; }


		void AddForce(SM_math::vec2& force);
		void Update(float dt);

		void SetMass(float mass);
		float GetInverseMass();

		void SetRenderingPos(Transform* trans);

		Collider* GetCollider();
		void SetCollider(Collider* c);

		SM_math::vec2& GetVelocity();
		void SetVelocity(SM_math::vec2& vel);

		float GetCor();
	};
}
