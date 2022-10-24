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
	void Render();

	void Add(GameObject* go);
	void Delete(GameObject* go);
};
