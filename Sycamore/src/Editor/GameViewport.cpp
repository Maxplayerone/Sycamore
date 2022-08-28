#include"GameViewport.h"

#include"imgui/imgui.h"

#include"../Utils/ObjectPool.h"
#include"../Utils/Settings.h"
#include"../Utils/Logger.h"

#include"../Buffers/Framebuffer.h"

#include"../../Math/SM_math.h"

#include"../InputHandling/MouseHandleler.h"

float screenRatio = 4 / 3;

ImVec2 GetMaxSizeForViewport() {
	ImVec2 maxSize;
	maxSize = ImGui::GetContentRegionAvail();

	maxSize.x -= ImGui::GetScrollX();
	maxSize.y -= ImGui::GetScrollY();

	//max dimensions available in imGui window
	//but with screen ration taken into account
	float aspectedWidth = maxSize.x;
	float aspectedHeight = aspectedWidth / screenRatio;

	if (aspectedHeight > maxSize.y) {
		aspectedHeight = maxSize.y;
		aspectedWidth = aspectedHeight * screenRatio;
	}

	return ImVec2(aspectedWidth, aspectedHeight);
}

ImVec2 GetCenteredPosForViewport(ImVec2& aspectSize) {
	ImVec2 maxSize;
	maxSize = ImGui::GetContentRegionAvail();

	maxSize.x -= ImGui::GetScrollX();
	maxSize.y -= ImGui::GetScrollY();

	float viewportX = (maxSize.x / 2.0f) - (aspectSize.x / 2.0f);
	float viewportY = (maxSize.y / 2.0f) - (aspectSize.y / 2.0f);

	return ImVec2(viewportX + ImGui::GetCursorPosX(), viewportY + ImGui::GetCursorPosY());
}

bool initializedFbo = false;
int framebufferID = -1;

ImVec2 windowSize;
ImVec2 windowPos;
ImVec2 topLeft;

void SM_Viewport::ImGui() {
	//add flags for scrolling
	ImGui::Begin("Game viewport", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	

	windowSize = GetMaxSizeForViewport();
	windowPos = GetCenteredPosForViewport(windowSize);

	//centers the texture
	ImGui::SetCursorPos(windowPos);
	topLeft = ImGui::GetWindowPos();

	if (!initializedFbo) {
		framebufferID = SM_Pool::GetFramebufferID(SM_settings::windowWidth, SM_settings::windowHeight);
		initializedFbo = true;
	}

	ImGui::Image((ImTextureID)SM_Pool::GetFramebufferTexSlot(), windowSize, ImVec2(0, 1), ImVec2(1, 0));
	bool result = MouseHandleler::Get().IsMouseOnWindow(SM_math::vec2(windowSize.x, windowSize.y), SM_math::vec2(topLeft.x, topLeft.y));
	if (result) LOGGER_INFO("The mouse is on the window");
	else LOGGER_WARNING("The mouse is not on the window");

	ImGui::End();
}