#pragma once
#include"ForceGenerator.h"

namespace SM_Physics {

	struct Registry {
		ForceGenerator* fg;
		Rigidbody* rb;
	};

	class ForceRegistry {
	private:
		std::vector<Registry> m_registry;
	public:
		void Add(ForceGenerator* fg, Rigidbody* rb);
		void UpdateForces(float dt);
	};
}
