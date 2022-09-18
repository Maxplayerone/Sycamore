#include"LevelEditorScene.h"

#include"../Rendering/Renderer.h"
#include"../Rendering/Texture.h"
#include"../Rendering/DebugDraw.h"

#include"../ECS/SpriteSheet.h"
#include"../ECS/SpriteRenderer.h"
#include"../ECS/Transform.h"

#include"../Utils/Profiler.h"
#include"../Utils/ObjectPool.h"
#include"../Utils/Settings.h"
#include"../Utils/Serializer.h"

#include"../InputHandling/MouseHandleler.h"

#include"imgui/imgui.h"

int firstBoxIndex = -1;

LevelEditorScene::LevelEditorScene() {
	this->m_renderer = new Renderer();	
	activeGameObject = new GameObject("NULL");

	//DebugDraw::AddBox2D({ 0.0f, 0.0f }, 128.0f, 45);
	//DebugDraw::AddCircle2D({ 0.0f, 00.0f }, 50.0f, { 0.54f, 0.95f, 0.36f });
}
int result = -1;

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
		result = CheckForClickedObject();
	}

	if (result > -1) {
		if (m_sceneObjects[result].GetID() == activeGameObject->GetID()) {
			MoveActiveObject();
		}
		else {
			*activeGameObject = m_sceneObjects[result];
			SM_math::vec2 center(activeGameObject->GetComponent<Transform>()->GetPos().x + activeGameObject->GetComponent<Transform>()->GetScale().x / 2, activeGameObject->GetComponent<Transform>()->GetPos().y + activeGameObject->GetComponent<Transform>()->GetScale().y / 2);
			firstBoxIndex = DebugDraw::AddBox2D(center, activeGameObject->GetComponent<Transform>()->GetScale().x, {1, 0.2, 0.3});

			result = -1;
		}
	}

	activeGameObject->ImGui();
	DebugDraw::Render();
	this->m_renderer->Render();	
}

int LevelEditorScene::AddGameObjectToScene(GameObject& go) {
	m_sceneObjects[m_sceneObjectsSize++] = go;
	this->m_renderer->Add(m_sceneObjects[m_sceneObjectsSize - 1]);
	SM_Serializer::Push(go);

	//current objectIndex;
	return m_sceneObjectsSize -1;
}

//------------------------------------------
//			MOVING ACTIVE GAME OBJECTS
//------------------------------------------

//function returns the index of the clicked object
//or -1 if no object has been clicked
int LevelEditorScene::CheckForClickedObject() {
	//deleting the gizmos on active game object
	
	for (int i = 0; i < 4; i++) {
		DebugDraw::SetLine2DIgnoreLifetime(firstBoxIndex + i , false);
	}
	
	SM_math::vec2 mouse = MouseHandleler::Get().GetMousePosModel();
	for (uint i = 0; i < m_sceneObjectsSize; i++) {
		SM_math::vec2 pos = m_sceneObjects[i].GetComponent<Transform>()->GetPos();
		SM_math::vec2 scale = m_sceneObjects[i].GetComponent<Transform>()->GetScale();

		if (mouse.x > pos.x && mouse.x < pos.x + scale.x && mouse.y > pos.y && mouse.y < pos.y + scale.y) {
				return i;	
		}
	}
	if(activeGameObject->GetName() != "NULL")
		SnapBlockToGrid();

	return -1;
}

void LevelEditorScene::MoveActiveObject() {

	SM_math::vec2 mousePos = MouseHandleler::Get().GetMousePosModel();
	activeGameObject->GetComponent<Transform>()->SetPosition(mousePos);
}

void LevelEditorScene::SnapBlockToGrid() {
	SM_math::vec2 pos = activeGameObject->GetComponent<Transform>()->GetPos();
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
	

	activeGameObject->GetComponent<Transform>()->SetPosition({ (float)finalX,  (float)finalY});
	result = -1;
}

//------------------------------------
//				ImGui
//------------------------------------


void LevelEditorScene::ImGui() {
	//cool blocks
	ImGui::Begin("Palette");	
	//normal shapes and texture
	{
		unsigned int spriteNum = 2;

		ImVec2 buttonSize(40, 40);
		ImGui::Text("Textures:");

		ImGuiStyle& style = ImGui::GetStyle();
		float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

		Texture* whiteSquare = SM_Pool::GetTexture("src/Assets/Images/WhiteSquare.png");
		Texture* amogus = SM_Pool::GetTexture("src/Assets/Images/amogus.jpg");
		for (int i = 0; i < spriteNum; i++)
		{
			ImGui::PushID(i);

			//probably should implement something better in the future
			if (i == 0) {
				if (ImGui::ImageButton((ImTextureID)whiteSquare->GetOpenGLTexID(), ImVec2(40, 40))) {
					GameObject go;
					go.AddComponent(new Transform({ 0.0f, 0.0f }));
					go.AddComponent(new SpriteRenderer({ 1.0f, 1.0f, 1.0f, 1.0f }));
					AddGameObjectToScene(go);
				}
			}
			else {
				if (ImGui::ImageButton((ImTextureID)amogus->GetOpenGLTexID(), ImVec2(40, 40), ImVec2(0,1), ImVec2(1, 0))) {
					GameObject go;
					go.AddComponent(new Transform({ 0.0f, 0.0f }));
					go.AddComponent(new SpriteRenderer(Sprite(amogus)));
					AddGameObjectToScene(go);
				}
			}

			float last_button_x2 = ImGui::GetItemRectMax().x;
			float next_button_x2 = last_button_x2 + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line

			if (i + 1 < spriteNum && next_button_x2 < window_visible_x2)
				ImGui::SameLine();

			ImGui::PopID();
		}
	}
	//spritesheets
	{
		unsigned int spriteNum = 81;
		SpriteSheet* sheet = SM_Pool::GetSpriteSheet("src/Assets/Images/blocks.png", 16, spriteNum);

		ImVec2 buttonSize(40, 40);
		ImGui::Text("Spritesheeet:");

		ImGuiStyle& style = ImGui::GetStyle();
		float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

		for (int i = 0; i < spriteNum; i++)
		{
			ImGui::PushID(i);

			Sprite spr = sheet->GetSprite(i);
			if (ImGui::ImageButton((ImTextureID)sheet->GetTexture()->GetOpenGLTexID(), ImVec2(40, 40), { spr.GetTexCoords()[0], spr.GetTexCoords()[1] }, { spr.GetTexCoords()[6], spr.GetTexCoords()[7] })) {
				GameObject go;
				go.AddComponent(new Transform({ 0.0f, 0.0f }));
				go.AddComponent(new SpriteRenderer(spr));
				AddGameObjectToScene(go);
			}

			float last_button_x2 = ImGui::GetItemRectMax().x;
			float next_button_x2 = last_button_x2 + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line

			if (i + 1 < spriteNum && next_button_x2 < window_visible_x2)
				ImGui::SameLine();

			ImGui::PopID();
		}
	}
	ImGui::End();
}

