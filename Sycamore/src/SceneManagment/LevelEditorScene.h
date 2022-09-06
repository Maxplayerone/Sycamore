#pragma once
#include"Scene.h"

#include"../Utils/DataTypes.h"

#include"../ECS/GameObject.h"

#define MAX_OBJECT_SIZE 1000

class LevelEditorScene : public Scene {
private:
	color4 bgColor = { 0.96f, 0.96f, 0.96f, 1.0f};

	GameObject m_sceneObjects[MAX_OBJECT_SIZE];
	uint m_sceneObjectsSize = 0;

	GameObject* activeGameObject;

	int CheckForClickedObject();
	void MoveActiveObject();
	void SnapBlockToGrid();
public:
	LevelEditorScene();

	void OnUpdate(float deltaTime) override;
	int AddGameObjectToScene(GameObject& go);

	void ImGui() override;
};
