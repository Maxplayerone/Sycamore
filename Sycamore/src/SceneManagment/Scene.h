#pragma once
#include"../smpch.h"

class Renderer;
class GameObject;

class Scene {
protected:
	Renderer* m_renderer;
public:
	Scene() {};

	virtual void OnUpdate(float deltaTime) {};

	virtual void AddGameObjectToScene(GameObject& go) {};

	virtual void ImGui() {};
};

