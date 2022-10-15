#include"PhysicsSystem.h"
#include"Primitives/Primitives.h"

namespace SM_Physics {

	PhysicsSystem::PhysicsSystem(float deltaTime, float gravityStrength)
	: m_fixedTimeFrame(deltaTime) {
		m_gravity = new Gravity(gravityStrength);
	}
	void PhysicsSystem::FixedUpdate() {
		m_pairs.clear();

		//check for collission
		//(this method sucks, probably should add spacial
		//partitioning or something along these lines)
		for (uint i = 0; i < m_bodies.size(); i++) {
			for (uint j = i; j < m_bodies.size(); j++) {
				//the outer and inner loop checks the
				//same rigidbody
				if (i == j) continue;

				Collider* c1 = m_bodies[i]->GetCollider();
				Collider* c2 = m_bodies[j]->GetCollider();
				CollissionInfo info = Collission_CircleAndCircle(c1, c2);

				if (info.hit == true) {
					collissionPair pair;
					pair.a = m_bodies[i];
					pair.b = m_bodies[j];
					pair.info = info;
					m_pairs.push_back(pair);
				}
			}
		}

		//update forces
		m_registry.UpdateForces(m_fixedTimeFrame);

		//iterative impulse resolution :D
		for (int k = 0; k < m_impulseIterations; k++) {
			for (int i = 0; i < m_pairs.size(); i++) {
				uint contactPoints = m_pairs[i].info.contactPointsAmount;
				for (int j = 0; j < contactPoints; j++) {
					Rigidbody* r1 = m_pairs[i].a;
					Rigidbody* r2 = m_pairs[i].b;
					ApplyImpulse(r1, r2, m_pairs[i].info);
				}
			}
		}

		for (auto rb : m_bodies) {
			rb->Update(m_fixedTimeFrame);
		}
	}

	void PhysicsSystem::ApplyImpulse(Rigidbody* a, Rigidbody* b, CollissionInfo info) {
		// Linear velocity
		float invMass1 = a->GetInverseMass();
		float invMass2 = b->GetInverseMass();
		float invMassSum = invMass1 + invMass2;
		if (invMassSum == 0.0f) {
			return;
		}

		// Relative velocity
		SM_math::vec2 relativeVel = b->GetVelocity() - a->GetVelocity();
		SM_math::vec2 relativeNormal = info.normal;

		//std::cout << "vel a " << a->GetVelocity() << " vel b " << b->GetVelocity() << std::endl;

		// Moving away from each other? Do nothing
		if (relativeVel * relativeNormal > 0.0f) {
			return;
		}

		float e = SM_math::MaxValue(a->GetCor(), b->GetCor());
		float numerator = (-(1.0f + e) * (relativeVel * relativeNormal));
		float j = numerator / invMassSum;
		if (info.contactPointsAmount > 0 && j != 0.0f) {
			j /= (float)info.contactPointsAmount;
		}

		SM_math::vec2 impulse = relativeNormal * j;

		SM_math::vec2 thingyOne = SM_math::vec2(impulse * invMass1 * -1.0f);
		SM_math::vec2 newVelA = a->GetVelocity() + thingyOne;
		a->SetVelocity(newVelA);

		SM_math::vec2 thingyTwo = SM_math::vec2(impulse * invMass2 * 1.0f);
		SM_math::vec2 newVelB = b->GetVelocity() + thingyTwo;
		b->SetVelocity(newVelB);
	}

	void PhysicsSystem::AddRigidbody(Rigidbody* rb, bool gravity) {
		m_bodies.push_back(rb);
		if(gravity)
			m_registry.Add(m_gravity, rb);
	}
}