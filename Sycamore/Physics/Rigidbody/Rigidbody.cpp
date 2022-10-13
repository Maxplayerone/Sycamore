#include"Rigidbody.h"

namespace SM_Physics {

	void Rigidbody::AddForce(SM_math::vec2& force) {
		m_forceAccum = m_forceAccum + force;
	}

	void Rigidbody::Update(float dt) {
		if (m_mass == 0.0f) return;

		SM_math::vec2 accel = m_forceAccum * m_inverseMass;
		m_velocity = m_velocity + accel * dt;

		pos = pos + m_velocity * dt;

		SyncWithRenderingPos();
		ClearAccum();
	}

	void Rigidbody::SetMass(float mass) {
		m_mass = mass;

		if (mass != 0.0f) m_inverseMass = 1.0f / mass;
	}

	void Rigidbody::ClearAccum() {
		m_forceAccum = SM_math::vec2(0.0f, 0.0f);
	}

	void Rigidbody::SetRenderingPos(Transform* trans) {
		m_renderingTrans = trans;
		pos = m_renderingTrans->GetPos();
	}
	void Rigidbody::SyncWithRenderingPos() {
		if (m_renderingTrans != nullptr)
			m_renderingTrans->SetPosition(pos);
	}
}