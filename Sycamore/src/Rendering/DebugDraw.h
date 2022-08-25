#pragma once
#include"../../Math/SM_math.h"
#include"../Utils/DataTypes.h"

namespace DebugDraw {
	void Render();

	void DrawDebugGrid();

	//lines 2D
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime);
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime);

	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color);
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end);

	//boxes 2D
	void AddBox2D(SM_math::vec2 center, float length, color3 color);
	void AddBox2D(SM_math::vec2 center, float length);

	void AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions, color3 color);
	void AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions);

	void AddBox2D(SM_math::vec2 center, float length, float angle, float lifetime);
	void AddBox2D(SM_math::vec2 center, float length, float angle);

	//circles 2D
	void AddCircle2D(SM_math::vec2 center, float radius, color3 color);
	
}