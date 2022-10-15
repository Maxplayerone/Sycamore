#pragma once
#include"Forces/ForceRegistry.h"
#include"Forces/Gravity.h"

#include"../src/smpch.h"

#include"Rigidbody/Rigidbody.h"
#include"Rigidbody/Collisions.h"

namespace SM_Physics {
	struct collissionPair {
		Rigidbody* a;
		Rigidbody* b;
		CollissionInfo info;
	};

	class PhysicsSystem {
	private:
		ForceRegistry m_registry;
		Gravity* m_gravity;

		float m_fixedTimeFrame = 0.0f;
		uint m_impulseIterations = 6;

		std::vector<Rigidbody*> m_bodies;
		std::vector<collissionPair> m_pairs;

		void ApplyImpulse(Rigidbody* a, Rigidbody* b, CollissionInfo info);
	public:
		PhysicsSystem(float deltaTime, float gravityStrength);
		void FixedUpdate();
		void AddRigidbody(Rigidbody* rb, bool gravity=true);
	};
}
