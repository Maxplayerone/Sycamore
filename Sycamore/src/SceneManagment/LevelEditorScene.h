#pragma once
#include"Scene.h"
#include"../Utils/DataTypes.h"

class LevelEditorScene : public Scene {
private:
	color4 bgColor = { 0.4f, 0.92f, 0.42f, 1.0f };
	GameObject* activeGameObject;
public:
	LevelEditorScene();

	void OnUpdate(float deltaTime) override;
	void AddGameObjectToScene(GameObject* go) override;

	void ImGui() override;
};
