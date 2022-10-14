#include"PhysicsSystem.h"
#include"Primitives/Primitives.h"

namespace SM_Physics {

	PhysicsSystem::PhysicsSystem(float deltaTime, float gravityStrength)
	: m_fixedTimeFrame(deltaTime) {
		m_gravity = new Gravity(gravityStrength);
	}
	void PhysicsSystem::FixedUpdate() {
		//check for collission
		//(this method sucks, probably should add spacial
		//partitioning or something along these lines)
		for (uint i = 0; i < m_bodies.size(); i++) {
			for (uint j = i; j < m_bodies.size(); j++) {
				//the outer and inner loop checks the
				//same rigidbody
				if (i == j) continue;

				Circle* c1 = m_bodies[i]->GetCollider();
				std::stringstream ss;
				ss << "circle " << c1->GetRadius() << " " << c1->rb->GetPos();
				LOGGER_INFO(ss.str());
			}
		}

		m_registry.UpdateForces(m_fixedTimeFrame);

		for (auto rb : m_bodies) {
			rb->Update(m_fixedTimeFrame);
		}
	}
	void PhysicsSystem::AddRigidbody(Rigidbody* rb, bool gravity) {
		m_bodies.push_back(rb);
		if(gravity)
			m_registry.Add(m_gravity, rb);
	}
}