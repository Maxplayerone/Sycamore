#pragma once
#include"Scene.h"
#include"../Utils/AssetsPool.h"

class LevelEditorScene : public Scene {
private:
	float BGcolor[4] = { 0.4f, 0.92f, 0.42f, 1.0f };
	GameObject* activeGameObject;
public:
	LevelEditorScene();

	void OnUpdate(float deltaTime) override;
	void AddGameObjectToScene(GameObject* go) override;

	void ImGui() override;
};
