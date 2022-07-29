#pragma once
#include"BatchRenderer.h"
#include"../ECS/GameObject.h"

class Renderer {
private:
	BatchRenderer* batch;
public:
	Renderer();

	void ChangeBGColor(float r, float g, float b, float a) const;
	void Add(GameObject* go);
	void Render();

	//renders a single object onto the scene
	void RenderDebug(GameObject* go);
};
