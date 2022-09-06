#pragma once
#include"../../Math/SM_math.h"
#include"../Utils/DataTypes.h"

namespace DebugDraw {
	void Render();

	void DrawDebugGrid();

	//lines 2D
	//with lifetime
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime);
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime);

	//without lifetime
	int AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color);
	int AddLine2D(SM_math::vec2 start, SM_math::vec2 end);

	//used specifically with the method without lifetime
	//to show/ delete them with the index given by those methods
	void SetLine2DIgnoreLifetime(int index, bool ignoreLifetime);

	//boxes 2D
	void AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions, color3 color, float lifetime);
	void AddBox2D(SM_math::vec2 center, float length, float angle, float lifetime);

	int AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions, color3 color);
	int AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions);


	int AddBox2D(SM_math::vec2 center, float length, color3 color);
	int AddBox2D(SM_math::vec2 center, float length);

	
	int AddBox2D(SM_math::vec2 center, float length, float angle);

	//circles 2D
	void AddCircle2D(SM_math::vec2 center, float radius, color3 color);
	
}