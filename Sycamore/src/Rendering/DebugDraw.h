#pragma once
#include"../../Math/SM_math.h"
#include"../Utils/DataTypes.h"

namespace DebugDraw {

	enum flag{ HAS_LIFETIME, IGNORE_LIFETIME, DESTROY_ON_FRAME };
	struct DebugLine2D {
	public:
		SM_math::vec2 start;
		SM_math::vec2 end;
		color3 color;
		flag lifetimeFlag;

		int LengthSquared();

		//is that line used
		//(in the line2D array)
		bool isDead = true;
	};

	void Render();

	void DrawDebugGrid();

	int AddLine2D(SM_math::vec2 start,	  SM_math::vec2 end, color3 color,	flag _flag = IGNORE_LIFETIME);
	int AddBox2D(SM_math::vec2 center,	  float length,		 color3 color, float _angle=0.0f,	flag _flag = IGNORE_LIFETIME);
	char AddCircle2D(SM_math::vec2 center, float radius,		 color3 color,	flag _flag = IGNORE_LIFETIME);

	//used specifically with the method without lifetime
	//to show/ delete them with the index given by those methods
	void SetLine2DLifetimeFlag(int index, flag _lifetimeFlag);
}