#include"LevelScene.h"

LevelScene::LevelScene() {
	this->m_renderer = new Renderer();
}

void LevelScene::OnUpdate(float deltaTime) {
	m_renderer->ChangeBGColor(BGcolor[0], BGcolor[1], BGcolor[2], BGcolor[3]);
}

void LevelScene::ImGui() {
}
