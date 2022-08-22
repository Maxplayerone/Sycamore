#pragma once

#include"../Utils/DataTypes.h"
#include"../../Math/SM_math.h"

class GameObject;
class BatchRenderer;

class Renderer {
private:
	BatchRenderer* batch;
public:
	Renderer();

	void ChangeBGColor(color4 color) const;
	void Add(GameObject& go);
	void Render();

};
