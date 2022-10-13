#pragma once
#include"../../Math/SM_math.h"
#include"../Utils/DataTypes.h"

namespace DebugDraw {

	enum flag{ HAS_LIFETIME, IGNORE_LIFETIME, DESTROY_ON_FRAME };
	struct DebugLine2D {
		SM_math::vec2 start;
		SM_math::vec2 end;
		color3 color;

		float lifetime;
		flag lifetimeFlag;

		//when the lifetime of the object
		//is 0 then the object is dead
		//and the bool is true
		//(other objects can you it's space
		//in the vertices buffer)

		//it is set to true at the beginning because if the array has no
		//linse then all lines are "dead"
		bool isDead = true;
		//should not be changed by any outside code

		int LengthSquared();
	};

	void Render();

	void DrawDebugGrid();

	//lines 2D
	//with lifetime
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime);
	void AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime);

	//without lifetime
	int AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, flag _flag=IGNORE_LIFETIME);
	int AddLine2D(SM_math::vec2 start, SM_math::vec2 end, flag _flag=IGNORE_LIFETIME);

	//used specifically with the method without lifetime
	//to show/ delete them with the index given by those methods
	void SetLine2DIgnoreLifetime(int index, flag _lifetimeFlag);

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