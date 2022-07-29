#include"LevelEditorScene.h"

LevelEditorScene::LevelEditorScene() {
	this->m_renderer = new Renderer();

	GameObject* coloredCube = new GameObject();
	coloredCube->AddComponent(new Transform(-0.5f, -0.5f));
	coloredCube->AddComponent(new SpriteRenderer(1.0f, 1.0f, 1.0f, 1.0f));
	AddGameObjectToScene(coloredCube);

	Texture* spriteSheetTex = AssetsPool::Get().GetTexture("src/Assets/Images/spritesheet.png");
	SpriteSheet* sheet = AssetsPool::Get().GetSpriteSheet(spriteSheetTex, 16, 26);

	GameObject* anotherCube = new GameObject();
	anotherCube->AddComponent(new Transform(1.0f, 0.0f));
	anotherCube->AddComponent(new SpriteRenderer(new Sprite(spriteSheetTex, sheet->GetSprite(3)->GetTexCoords())));
	AddGameObjectToScene(anotherCube);

	activeGameObject = m_gameObjects[0];
}

void LevelEditorScene::OnUpdate(float deltaTime) {
	this->m_renderer->ChangeBGColor(BGcolor[0], BGcolor[1], BGcolor[2], BGcolor[3]);
	
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->Update(deltaTime);
	}
	activeGameObject->ImGui();

	this->m_renderer->Render();
}

void LevelEditorScene::AddGameObjectToScene(GameObject* go) {
	auto itr = std::find(this->m_gameObjects.begin(), this->m_gameObjects.end(), go);
	//the game object is already in the vector
	if (itr != this->m_gameObjects.end()) return;

	this->m_gameObjects.push_back(go);
	this->m_renderer->Add(m_gameObjects[m_gameObjects.size() - 1]);
}


void LevelEditorScene::ImGui() {
	ImGui::Begin("Level editor scene");
	ImGui::ColorEdit4("BG color", BGcolor);
	ImGui::End();
}
