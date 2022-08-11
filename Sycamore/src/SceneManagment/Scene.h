#pragma once
#include<iostream>

//shadering
#include"../Shadering/Renderer.h"
#include"../Shadering/Texture.h"

//ecs
#include"../ECS/SpriteRenderer.h"
#include"../ECS/Transform.h"
#include"../ECS/GameObject.h"
#include"../ECS/SpriteSheet.h"

#include"../Utils/DataTypes.h"

#include"imgui/imgui.h"

class Scene {
protected:
	Renderer* m_renderer;
	std::vector<GameObject*> m_gameObjects;
public:
	Scene() {};

	virtual void OnUpdate(float deltaTime) {};

	virtual void AddGameObjectToScene(GameObject* go) {};

	virtual void ImGui() {};
};

