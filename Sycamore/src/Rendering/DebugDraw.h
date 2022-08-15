#pragma once
#include"../../Math/SM_math.h"
#include"../Utils/DataTypes.h"

namespace DebugDraw {

	void Start();
	void Render();

	//lines 2D
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime);
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime);
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end);
}