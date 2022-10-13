#pragma once
#include"Forces/ForceRegistry.h"
#include"Forces/Gravity.h"

#include"../src/smpch.h"

#include"Rigidbody/Rigidbody.h"

namespace SM_Physics {

	class PhysicsSystem {
	private:
		ForceRegistry m_registry;
		Gravity* m_gravity;

		float m_fixedTimeFrame = 0.0f;

		std::vector<Rigidbody*> m_bodies;
	public:
		PhysicsSystem(float deltaTime, float gravityStrength);
		void FixedUpdate();
		void AddRigidbody(Rigidbody* rb);
	};
}
