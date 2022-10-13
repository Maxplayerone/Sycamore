#pragma once
#include"ForceGenerator.h"

namespace SM_Physics {

	class Gravity : public ForceGenerator {
	private:
		float m_gravityStrength = 0.0f;
	public:
		Gravity(float strength);
		void UpdateForce(Rigidbody* rb, float dt) override;
	};
}
