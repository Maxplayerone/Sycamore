#pragma once
#include"../../Math/SM_math.h"
#include"../Utils/DataTypes.h"

namespace DebugDraw {

	struct DebugLine2D {
	public:
		SM_math::vec2 start;
		SM_math::vec2 end;
		color3 color;

		int LengthSquared();
	};

	void Render();

	void DrawDebugGrid();

	void AddLine2D(SM_math::vec2 start,	SM_math::vec2 end, color3 color);
	void AddBox2D(SM_math::vec2 center, float length, color3 color, float _angle=0.0f);
	void AddCircle2D(SM_math::vec2 center, float radius, color3 color);
}