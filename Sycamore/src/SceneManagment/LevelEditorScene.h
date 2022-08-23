#pragma once
#include"Scene.h"

#include"../Utils/DataTypes.h"

#include"../ECS/SpriteRenderer.h"
#include"../ECS/Transform.h"
#include"../ECS/GameObject.h"

#define MAX_OBJECT_SIZE 1000

class LevelEditorScene : public Scene {
private:
	color4 bgColor = { 0.96f, 0.96f, 0.96f, 1.0f};

	GameObject m_sceneObjects[MAX_OBJECT_SIZE];
	uint m_sceneObjectsSize = 0;

	GameObject activeGameObject;

	int CheckForActiveGameObject();
	void MoveClickedBlock(uint goIndex);
public:
	LevelEditorScene();

	void OnUpdate(float deltaTime) override;
	void AddGameObjectToScene(GameObject& go) override;

	void ImGui() override;
};
