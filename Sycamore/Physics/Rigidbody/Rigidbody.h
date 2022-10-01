#pragma once
#include"../../Math/SM_math.h"

namespace SM_Physics {
	struct Rigidbody {
		SM_math::vec2 pos = { 0.0f, 0.0f};
		float rotation = 0.0f;

		//creating a dummy rigidbody
		Rigidbody() :
			pos(SM_math::vec2(0.0f)), rotation(0.0f) {}

		//we are explicitely setting the variables
	};
}
