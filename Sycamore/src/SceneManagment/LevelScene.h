#pragma once
#include"Scene.h"
#include"../Utils/DataTypes.h"

class LevelScene : public Scene {
private:
	color4 bgColor = { 0.44f, 0.47f, 0.97f, 1.0f };
public:
	LevelScene();
	void OnUpdate(float deltaTime) override;
	void ImGui() override;
};

