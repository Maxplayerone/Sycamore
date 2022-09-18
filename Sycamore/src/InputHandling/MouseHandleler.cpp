#include"MouseHandleler.h"

#include"../smpch.h"

#include"../Utils/Logger.h"
#include"../Utils/Settings.h"

#include"imgui/imgui.h"

MouseHandleler::MouseHandleler(){
	for (int i = 0; i < 3; i++)
		mouseButtons[i] = false;
}

bool MouseHandleler::IsMouseButtonPressed(int button) {
	if (button > MouseHandleler::Get().ArrayLength()) return false;

	bool answer = MouseHandleler::Get().mouseButtons[button];
	MouseHandleler::Get().mouseButtons[button] = false;

	return answer;
}

void MouseHandleler::SetScrollInput(double x, double y) {
	if (x != 0)
		offset.x = x;
	if (y != 0)
		offset.y = y;
}

bool MouseHandleler::IsScrolling() {
	return offset.x != 0 || offset.y != 0 ? true : false;
}

void MouseHandleler::SetMousePosAbsolute(double x, double y) {
	position.x = x;
	position.y = y;
}

void MouseHandleler::SetMousePosModel() {
	posModel.x = (viewportAbsPos.x - ((float)SM_settings::windowWidth / 2));
	posModel.y = -((viewportAbsPos.y - ((float)SM_settings::windowHeight / 2)));
}

void MouseHandleler::PrintMousePosAbs() {
	std::stringstream ss;
	ss << "Mouse position  x " << position.x << " mouse position y " << position.y;
	LOGGER_INFO(ss.str());
}

void MouseHandleler::PrintMousePosModel() {
	SetMousePosModel();

	std::stringstream ss;
	ss << "Mouse position  " << posModel;
	LOGGER_INFO(ss.str());
}

void MouseHandleler::PrintMousePosViewport() {
	std::stringstream ss;
	ss << "Mouse position  x " << viewportAbsPos.x << " mouse position y " << viewportAbsPos.y;
	//LOGGER_INFO(ss.str());
}

void MouseHandleler::SetMousePosViewport(SM_math::vec2 windowSize, SM_math::vec2 windowPos) {
	viewportPos = SM_math::vec2(windowPos.x, windowPos.y);
	viewportSize = SM_math::vec2(windowSize.x, windowSize.y);

	viewportAbsPos = position;

	float scaleFactorX = (float)SM_settings::windowWidth / viewportSize.x;
	float scaleFactorY = (float)SM_settings::windowHeight / viewportSize.y;

	//made to combat the padding of imgui window
	float offsetX = 10.0f;
	float offsetY = 30.0f;

	viewportAbsPos.x = (viewportAbsPos.x - viewportPos.x - offsetX) * scaleFactorX;
	viewportAbsPos.y = (viewportAbsPos.y - viewportPos.y - offsetY) * scaleFactorY;
}

