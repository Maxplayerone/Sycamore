#pragma once
#include"Scene.h"

#include"../Utils/DataTypes.h"

#include"../ECS/GameObject.h"

#define MAX_OBJECT_SIZE 1000

class LevelEditorScene : public Scene {
private:
	color4 bgColor = { 0.96f, 0.96f, 0.96f, 0.8f};

	GameObject m_sceneObjects[MAX_OBJECT_SIZE];
	uint m_sceneObjectsSize = 0;
public:
	LevelEditorScene();
	//used to instantiate some object that we want to use
	//during runtime and assets
	void LoadData();

	void OnUpdate(float deltaTime) override;
	void OnUpdateRuntime(float deltaTime);
	int AddGameObjectToScene(GameObject& go);

	void ImGui() override;
	void CleanUp();
};
