#include"PhysicsSystem.h"

namespace SM_Physics {

	PhysicsSystem::PhysicsSystem(float deltaTime, float gravityStrength)
	: m_fixedTimeFrame(deltaTime) {
		m_gravity = new Gravity(gravityStrength);
	}
	void PhysicsSystem::FixedUpdate() {
		m_registry.UpdateForces(m_fixedTimeFrame);

		for (auto rb : m_bodies) {
			rb->Update(m_fixedTimeFrame);
		}
	}
	void PhysicsSystem::AddRigidbody(Rigidbody* rb) {
		m_bodies.push_back(rb);
		m_registry.Add(m_gravity, rb);
	}
}