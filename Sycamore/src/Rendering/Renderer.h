#pragma once

#include"../Utils/DataTypes.h"

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

	//renders a single object onto the scene
	void RenderDebug(GameObject& go);
};
