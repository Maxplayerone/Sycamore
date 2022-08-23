#include"MouseHandleler.h"

#include"../smpch.h"

#include"../Utils/Logger.h"
#include"../Utils/Settings.h"

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

