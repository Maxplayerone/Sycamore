#pragma once
#include"../Rigidbody/Rigidbody.h"

namespace SM_Physics {

	class ForceGenerator {
	public:
		virtual void UpdateForce(Rigidbody* rb, float dt) = 0;
	};
}
