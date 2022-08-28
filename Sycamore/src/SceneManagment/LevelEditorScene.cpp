#include"LevelEditorScene.h"

#include"../Rendering/Renderer.h"
#include"../Rendering/Texture.h"
#include"../Rendering/DebugDraw.h"

#include"../ECS/SpriteSheet.h"

#include"../Utils/Profiler.h"
#include"../Utils/ObjectPool.h"
#include"../Utils/Settings.h"

#include"../InputHandling/MouseHandleler.h"

#include"imgui/imgui.h"

LevelEditorScene::LevelEditorScene() {
	this->m_renderer = new Renderer();	

	GameObject coloredCube;
	coloredCube.AddComponent(new Transform({ 0.0f, 0.0f }, { 32.0f, 32.0f }));
	coloredCube.AddComponent(new SpriteRenderer({ 0.8f, 0.32f, 0.92f, 1.0f }));
	AddGameObjectToScene(coloredCube);

	SpriteSheet* sheet = SM_Pool::GetSpriteSheet("blocks.png", 16, 81);


	GameObject anotherCube;
	anotherCube.AddComponent( new Transform({64.0f, 0.0f}, {32.0f, 32.0f}) );
	anotherCube.AddComponent( new SpriteRenderer( sheet->GetSprite(5) ) );

	AddGameObjectToScene(anotherCube);
	
	activeGameObject = m_sceneObjects[0];

	//DebugDraw::AddBox2D({ 0.0f, 0.0f }, 128.0f, 45);
	DebugDraw::AddCircle2D({ 0.0f, 00.0f }, 50.0f, { 0.54f, 0.95f, 0.36f });
}
int result = -2;

void LevelEditorScene::OnUpdate(float deltaTime) {
	SM_Profiler::MAIN("LevelEditorScene update");

	this->m_renderer->ChangeBGColor(bgColor);

	{
		SM_Profiler::MAIN("LevelEditorScene gameObject updating");
		for (int i = 0; i < m_sceneObjectsSize; i++) {

			m_sceneObjects[i].Update(deltaTime);
		}
	}

	if (MouseHandleler::Get().IsMouseButtonPressed(0)) {
		if (canSnapBlock)
			SnapBlockToGrid();
		else
			result = CheckForActiveGameObject();
	}

	activeGameObject.ImGui();

	if (result > -1)
		MoveClickedBlock(result);	

	DebugDraw::Render();
	this->m_renderer->Render();	
}

int LevelEditorScene::CheckForActiveGameObject() {
	SM_math::vec2 mouse = MouseHandleler::Get().GetMousePosModel();
	for (uint i = 0; i < m_sceneObjectsSize; i++) {
		SM_math::vec2 pos = m_sceneObjects[i].GetComponent<Transform>()->GetPos();
		SM_math::vec2 scale = m_sceneObjects[i].GetComponent<Transform>()->GetScale();

		if (mouse.x > pos.x && mouse.x < pos.x + scale.x && mouse.y > pos.y && mouse.y < pos.y + scale.y) {
			activeGameObject = m_sceneObjects[i];
			canSnapBlock = true;
			return i;
		}
	}
	return -1;
}

void LevelEditorScene::MoveClickedBlock(uint gameObjectIndex) {

	SM_math::vec2 mousePos = MouseHandleler::Get().GetMousePosModel();
	m_sceneObjects[gameObjectIndex].GetComponent<Transform>()->SetPosition(mousePos);
}

void LevelEditorScene::SnapBlockToGrid() {
	SM_math::vec2 pos = activeGameObject.GetComponent<Transform>()->GetPos();
	int finalX;
	int finalY;

	int widthError = (int)pos.x % SM_settings::GRID_WIDTH;
	//closer to the right side
	if (widthError >= SM_settings::GRID_WIDTH / 2) {
		int widthCorrection = SM_settings::GRID_WIDTH - widthError;
		finalX = pos.x + widthCorrection;
	}
	else {
		finalX = pos.x - widthError;
	}

	int heightError = (int)pos.y % SM_settings::GRID_HEIGHT;

	if (heightError >= SM_settings::GRID_HEIGHT / 2) {
		int heightCorrection = SM_settings::GRID_HEIGHT - heightError;
		finalY = pos.y + heightCorrection;
	}
	else {
		finalY = pos.y - heightError;
	}
	

	activeGameObject.GetComponent<Transform>()->SetPosition({ (float)finalX,  (float)finalY});

	canSnapBlock = false;
	result = -1;
}
int LevelEditorScene::AddGameObjectToScene(GameObject& go) {
	/*
	auto itr = std::find(this->m_gameObjects.begin(), this->m_gameObjects.end(), go);
	//the game object is already in the vector
	if (itr != this->m_gameObjects.end()) return;
	*/

	m_sceneObjects[m_sceneObjectsSize++] = go;
	//we're accessing an array index, which starts at 0 (that's why we decrease by one)
	this->m_renderer->Add(m_sceneObjects[m_sceneObjectsSize - 1]);

	//current objectIndex;
	return m_sceneObjectsSize - 1;
}


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
			go.AddComponent(new Transform({0.0f, 0.0f}));
			//MouseHandleler::Get().DebugCheckMousePosModel();
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
