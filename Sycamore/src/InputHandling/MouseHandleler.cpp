#include"MouseHandleler.h"

#include"../smpch.h"

#include"../Utils/Logger.h"
#include"../Utils/Settings.h"

#include"imgui/imgui.h"

SM_math::mat4 projMat(1.0f);

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

void MouseHandleler::GetProjectionMatrix(SM_math::mat4 _projMat) {
	projMat = _projMat;
}

void MouseHandleler::SetMousePosModel() {
	posModel.x = position.x - ((float)SM_settings::windowWidth / 2);
	posModel.y = -(position.y - ((float)SM_settings::windowHeight / 2));
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

bool MouseHandleler::IsMouseOnWindow(SM_math::vec2 windowSize, SM_math::vec2 windowPos) {
	float leftOffsetX = 130.0f;
	float topOffsetY = 150.0f;
	float rightOffsetX = 130.0f;
	float bottomOffsetY = 20.0f;

	/*
	if (position.x > windowPos.x + leftOffsetX && position.x < windowPos.x + windowSize.x + rightOffsetX && position.y > windowPos.y + topOffsetY && position.y < windowPos.y + windowSize.y + bottomOffsetY) {
		float leftBorder = windowPos.x + leftOffsetX;
		float rightBorder = windowPos.x + windowSize.x + rightOffsetX;
		std::stringstream ss;
		ss << "left border " << leftBorder << " right border " << rightBorder;
		LOGGER_INFO(ss.str());

		return true;
	}
	*/

	std::stringstream ss;
	ss << "Mous pos x " << posModel.x - windowPos.x << "and y " << posModel.y - windowPos.y;
	LOGGER_INFO(ss.str());
	//-480 = windowPos.x + leftOffsetX
	//480 = windowPos.x + windowSize.x + rightOffsetX
	
	return false;
}

