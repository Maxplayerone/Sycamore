#pragma once
#include"../../Math/SM_math.h"

namespace SM_Physics {
	struct Rigidbody {
	private:
		SM_math::vec2 pos = { 0.0f, 0.0f};
		float rotation = 0.0f;

	public:
		//creating a dummy rigidbody
		Rigidbody() :
			pos(SM_math::vec2(0.0f)), rotation(0.0f) {}

		Rigidbody(float angle) :
			pos(SM_math::vec2(0.0f)), rotation(angle) {}

		Rigidbody(SM_math::vec2& pos):
			pos(pos), rotation(0.0f) {}

		SM_math::vec2& GetPos() { return pos; }
		float GetRotation() { return rotation; }

		void SetPos(SM_math::vec2& _pos) { pos = _pos; }
		void SetRotation(float angle) { rotation = angle; }
	};
}
