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

#include"../../Physics/PhysicsSystem.h"
#include"../../Physics/Primitives/Primitives.h"

GameObject activeGameObject;

int result = -3;
//(-3) user didn't click any mouse button
//(-2) user didn't click on any object
//(-1) user clicked on an active game object
//(i) user clicked on i'th object in m_sceneObjects array
enum activeObjectState {NO_STATE, STATE_MOVING, STATE_CLICKED};
//STATE_MOVING just clicked the active object. The object should follow the mouse
//STATE_CLICKED just clicked active object when it was following the cursor.
//the object should have an outline
activeObjectState state = activeObjectState::NO_STATE;
//currently active object
int activeObjectIndex = -1;


LevelEditorScene::LevelEditorScene() {
	this->m_renderer = new Renderer();	
	activeGameObject = GameObject("NULL");
}

static int CheckCollissionMouseAndObject(int size, GameObject* objects) {

	SM_math::vec2 mouse = MouseHandleler::Get().GetMousePosModel();
	for (uint i = 0; i < size; i++) {
		SM_math::vec2 pos = objects[i].GetComponent<Transform>()->GetPos();
		SM_math::vec2 scale = objects[i].GetComponent<Transform>()->GetScale();

		if (mouse.x > pos.x && mouse.x < pos.x + scale.x && mouse.y > pos.y && mouse.y < pos.y + scale.y) {
			GameObject clickedObj = objects[i];

			if (activeGameObject.GetName() != "NULL" && clickedObj.GetID() == activeGameObject.GetID()) {
				//the clicked object is the active game object
				state = activeObjectState::STATE_MOVING;
				return -1;
			}
			else {
				//this is a new object that should become active
				state = activeObjectState::STATE_CLICKED;
				activeObjectIndex = i;
				return i;
			}
		}
	}

	return -2;
}

static void SnapObjectToGrid() {
	if (activeGameObject.GetName() == "NULL") {
		return;
	}

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


	activeGameObject.GetComponent<Transform>()->SetPosition({ (float)finalX,  (float)finalY });
}

static void MoveActiveObject() {
	if (activeGameObject.GetName() == "NULL") {
		return;
	}

	SM_math::vec2 mousePos = MouseHandleler::Get().GetMousePosModel();
	activeGameObject.GetComponent<Transform>()->SetPosition(mousePos);
}

static void DrawActiveGameObjectOutline() {
	if (activeGameObject.GetName() == "NULL") {
		return;
	}

	SM_math::vec2 center(activeGameObject.GetComponent<Transform>()->GetPos().x + activeGameObject.GetComponent<Transform>()->GetScale().x / 2, activeGameObject.GetComponent<Transform>()->GetPos().y + activeGameObject.GetComponent<Transform>()->GetScale().y / 2);
	DebugDraw::AddBox2D(center, activeGameObject.GetComponent<Transform>()->GetScale().x, { 1, 0.2, 0.3 });
}

static int CheckForMouseInput(int size, GameObject* objects, Renderer* rend) {
	//clicked active object? It should follow the cursor
	if (state == activeObjectState::STATE_MOVING) {
		if (MouseHandleler::Get().IsMouseButtonPressed(0)) {
			state = activeObjectState::NO_STATE;
			return -2;
		}
		else
			return -1;
	}

	else if (state == activeObjectState::STATE_CLICKED)
		DrawActiveGameObjectOutline();

	
	//check if we pressed any object
	if (MouseHandleler::Get().IsMouseButtonPressed(0))
		CheckCollissionMouseAndObject(size, objects);
	else if (MouseHandleler::Get().IsMouseButtonPressed(1)) {
		int result = -2;
		if ((result = CheckCollissionMouseAndObject(size, objects)) != -2) {
			rend->Delete(&objects[result]);
			objects[result].Destroy();
			return -3;
		}
	}
	else
		return -3;
}

static void ResolveMouseInputRequest(GameObject* objects) {
	switch (result) {
	case -3:
		break;
	case -2:
		//LOGGER_INFO("didn't click any object");
		SnapObjectToGrid();
		break;
	case -1:
		//LOGGER_INFO("clicked active game object");
		MoveActiveObject();
		break;
	default:
		//LOGGER_INFO("click an object that is not active");
		activeGameObject = objects[result];
		DrawActiveGameObjectOutline();
		break;
	}
}

void LevelEditorScene::OnUpdate(float deltaTime) {
	SM_Profiler::MAIN("LevelEditorScene update");

	this->m_renderer->ChangeBGColor(bgColor);
	
	result = CheckForMouseInput(m_sceneObjectsSize, m_sceneObjects, m_renderer);
	ResolveMouseInputRequest(m_sceneObjects);

	//rendering and imgui
	activeGameObject.ImGui();
	DebugDraw::Render();
	this->m_renderer->Render();	
}

int LevelEditorScene::AddGameObjectToScene(GameObject& go) {
	m_sceneObjects[m_sceneObjectsSize++] = go;
	this->m_renderer->Add(&m_sceneObjects[m_sceneObjectsSize - 1]);
	SM_Serializer::Push(go);

	//current objectIndex;
	return m_sceneObjectsSize - 1;
}

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
					go.AddComponent(new Transform(SM_math::vec2(0.0f, 0.0f)));
					go.AddComponent(new SpriteRenderer({ 1.0f, 1.0f, 1.0f, 1.0f }));
					AddGameObjectToScene(go);

				}
			}
			else {
				if (ImGui::ImageButton((ImTextureID)amogus->GetOpenGLTexID(), ImVec2(40, 40), ImVec2(0, 1), ImVec2(1, 0))) {

					GameObject go;
					go.AddComponent(new Transform(SM_math::vec2(0.0f, 0.0f)));
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
				go.AddComponent(new Transform(SM_math::vec2(0.0f, 0.0f)));
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

void LevelEditorScene::CleanUp() {
	for (int i = 0; i < m_sceneObjectsSize; i++) {
		m_renderer->Delete(&m_sceneObjects[i]);
		m_sceneObjects[i].Destroy();
	}
	m_sceneObjectsSize = 0;
}



