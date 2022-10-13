#include"ForceRegistry.h"

namespace SM_Physics {
	void ForceRegistry::Add(ForceGenerator* fg, Rigidbody* rb) {
		Registry r;
		r.fg = fg;
		r.rb = rb;
		m_registry.push_back(r);
	}

	void ForceRegistry::UpdateForces(float dt) {
		for (auto registry : m_registry) {
			registry.fg->UpdateForce(registry.rb, dt);
		}
	}
}