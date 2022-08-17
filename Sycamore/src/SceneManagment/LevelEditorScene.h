#pragma once
#include"Scene.h"
#include"../Utils/DataTypes.h"

class LevelEditorScene : public Scene {
private:
	color4 bgColor = { 0.96f, 0.96f, 0.96f, 1.0f};
	GameObject* activeGameObject;
public:
	LevelEditorScene();

	void OnUpdate(float deltaTime) override;
	void AddGameObjectToScene(GameObject* go) override;

	void ImGui() override;
};
