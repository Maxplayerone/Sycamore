#include"LevelEditorScene.h"

LevelEditorScene::LevelEditorScene() {
	this->m_renderer = new Renderer();

	GameObject* coloredCube = new GameObject();
	coloredCube->AddComponent(new Transform({-100.0f, 0.0f}, {100.0f, 100.0f}));
	coloredCube->AddComponent(new SpriteRenderer({ 0.8f, 0.32f, 0.92f, 1.0f }));
	AddGameObjectToScene(coloredCube);

	SpriteSheet* sheet = AssetsPool::Get().GetSpriteSheet("blocks.png", 16, 81);

	GameObject* anotherCube = new GameObject();
	anotherCube->AddComponent(new Transform({50.0f, -30.0f}, {50.0f, 50.0f}));
	anotherCube->AddComponent(new SpriteRenderer(AssetsPool::Get().GetTexture("amogus.jpg")->GetSlot()));
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
	//scene color changing
	ImGui::Begin("Level editor scene");
	ImGui::ColorEdit4("BG color", BGcolor);
	ImGui::End();

	//cool blocks
	ImGui::Begin("Blocks");	
	Texture* tex = AssetsPool::Get().GetTexture("blocks.png");
	unsigned int spriteNum = 81;

	SpriteSheet* sheet = AssetsPool::Get().GetSpriteSheet("blocks.png", 16, 81);

	ImVec2 buttonSize(40, 40);
	ImGui::Text("Manually wrapping:");

	ImGuiStyle& style = ImGui::GetStyle();
	float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

	for (int i = 0; i < spriteNum; i++)
	{
		ImGui::PushID(i);

		Sprite* spr = sheet->GetSprite(i);
		ImGui::ImageButton((ImTextureID)sheet->GetTexture()->GetSlot(), ImVec2(40, 40), { spr->GetTexCoords()[0], spr->GetTexCoords()[1] }, { spr->GetTexCoords()[6], spr->GetTexCoords()[7] });

		float last_button_x2 = ImGui::GetItemRectMax().x;
		float next_button_x2 = last_button_x2 + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line

		if (i + 1 < spriteNum && next_button_x2 < window_visible_x2)
			ImGui::SameLine();

		ImGui::PopID();
	}
	ImGui::End();
}
