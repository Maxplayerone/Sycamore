#include"LevelEditorScene.h"

#include"../Rendering/Renderer.h"
#include"../Rendering/Texture.h"
#include"../Rendering/DebugDraw.h"

#include"../ECS/SpriteRenderer.h"
#include"../ECS/Transform.h"
#include"../ECS/GameObject.h"
#include"../ECS/SpriteSheet.h"

#include"../Utils/Profiler.h"
#include"../Utils/ObjectPool.h"

#include"../InputHandling/MouseHandleler.h"

#include"imgui/imgui.h"

LevelEditorScene::LevelEditorScene() {
	this->m_renderer = new Renderer();	

	GameObject coloredCube;
	coloredCube.AddComponent(new Transform({0.0f, 0.0f}, {32.0f, 32.0f}));
	coloredCube.AddComponent(new SpriteRenderer({ 0.8f, 0.32f, 0.92f, 1.0f }));
	AddGameObjectToScene(coloredCube);

	SpriteSheet* sheet = SM_Pool::GetSpriteSheet("blocks.png", 16, 81);


	GameObject anotherCube;
	anotherCube.AddComponent(new Transform({64.0f, 0.0f}, {32.0f, 32.0f}));
	anotherCube.AddComponent( new SpriteRenderer( sheet->GetSprite(5) ) );

	AddGameObjectToScene(anotherCube);
	
	activeGameObject = m_sceneObjects[0];

	DebugDraw::DrawDebugGrid();
	DebugDraw::AddLine2D({ 0.0f, 0.0f }, { 100.0f, 100.0f }, { 0.0f, 0.0f, 0.0f }, 120.0f);
	DebugDraw::AddLine2D({ -100.0f, -100.0f }, { -200.0f, -200.0f }, { 0.0f, 0.0f, 0.0f }, 240.0f);
}

void LevelEditorScene::OnUpdate(float deltaTime) {
	SM_Profiler::MAIN("LevelEditorScene update");

	this->m_renderer->ChangeBGColor(bgColor);

	{
		SM_Profiler::MAIN("LevelEditorScene gameObject updating");
		for (int i = 0; i < m_sceneObjectsSize; i++) {

			m_sceneObjects[i].Update(deltaTime);
		}
	}
	activeGameObject.ImGui();

	DebugDraw::Render();
	this->m_renderer->Render();	
}

void LevelEditorScene::AddGameObjectToScene(GameObject&  go) {
	/*
	auto itr = std::find(this->m_gameObjects.begin(), this->m_gameObjects.end(), go);
	//the game object is already in the vector
	if (itr != this->m_gameObjects.end()) return;
	*/
	m_sceneObjects[m_sceneObjectsSize++] = go;
	std::stringstream ss;
	ss << "Game object count " << m_sceneObjectsSize;
	//we're accessing an array index, which starts at 0 (that's why we decrease by one)
	this->m_renderer->Add(m_sceneObjects[m_sceneObjectsSize - 1]);
}

//teleports the block that was clicked by a mouse
//to it's cursor position
void MoveClickedBlock() {
}

static float posX = 0;
void LevelEditorScene::ImGui() {
	//scene color changing
	ImGui::Begin("Level editor scene");
	ImGui::SliderFloat("bg color r", &bgColor.r, 0.0f, 1.0f);
	ImGui::SliderFloat("bg color g", &bgColor.g, 0.0f, 1.0f);
	ImGui::SliderFloat("bg color b", &bgColor.b, 0.0f, 1.0f);
	ImGui::End();

	//cool blocks
	ImGui::Begin("Blocks");	
	unsigned int spriteNum = 81;

	SpriteSheet* sheet = SM_Pool::GetSpriteSheet("blocks.png", 16, 81);

	ImVec2 buttonSize(40, 40);
	ImGui::Text("Manually wrapping:");

	ImGuiStyle& style = ImGui::GetStyle();
	float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

	for (int i = 0; i < spriteNum; i++)
	{
		ImGui::PushID(i);

		Sprite* spr = sheet->GetSprite(i);
		
		if (ImGui::ImageButton((ImTextureID)sheet->GetTexture()->GetSlot(), ImVec2(40, 40), { spr->GetTexCoords()[0], spr->GetTexCoords()[1] }, { spr->GetTexCoords()[6], spr->GetTexCoords()[7] })) {
			
			GameObject go;
			//go.AddComponent(new Transform({MouseHandleler::Get().GetMousePosAbs().x, MouseHandleler::Get().GetMousePosAbs().y}));
			go.AddComponent(new Transform({1.0f, 1.0f}));
			//MouseHandleler::Get().DebugCheckMouesPos();
			go.AddComponent(new SpriteRenderer(spr));
			AddGameObjectToScene(go);
			
		}
		
		float last_button_x2 = ImGui::GetItemRectMax().x;
		float next_button_x2 = last_button_x2 + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line

		if (i + 1 < spriteNum && next_button_x2 < window_visible_x2)
			ImGui::SameLine();

		ImGui::PopID();
	}
	ImGui::End();
}
