#pragma once
#include"Scene.h"

#include"../Shadering/Renderer.h"

class LevelScene : public Scene {
private:
	float BGcolor[4] = { 0.44f, 0.47f, 0.97f, 1.0f };
public:
	LevelScene();
	void OnUpdate(float deltaTime) override;
	void ImGui() override;
};

