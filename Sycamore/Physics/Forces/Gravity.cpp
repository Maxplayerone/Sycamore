#include"Gravity.h"

namespace SM_Physics {

	Gravity::Gravity(float strength)
	:m_gravityStrength(strength) {

	}
	void Gravity::UpdateForce(Rigidbody* rb, float dt) {
		rb->AddForce(SM_math::vec2(0.0f, -m_gravityStrength));
	}
}