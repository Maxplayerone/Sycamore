#include"LevelScene.h"

#include"imgui/imgui.h"

#include"../Rendering/Renderer.h"

LevelScene::LevelScene() {
	this->m_renderer = new Renderer();
}

void LevelScene::OnUpdate(float deltaTime) {
	m_renderer->ChangeBGColor(bgColor);
}

void LevelScene::ImGui() {
	ImGui::Begin("Level editor scene");
	ImGui::SliderFloat("bg color r", &bgColor.r, 0.0f, 1.0f);
	ImGui::SliderFloat("bg color g", &bgColor.g, 0.0f, 1.0f);
	ImGui::SliderFloat("bg color b", &bgColor.b, 0.0f, 1.0f);
	ImGui::End();
}
