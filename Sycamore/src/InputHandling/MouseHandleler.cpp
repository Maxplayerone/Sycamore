#include"MouseHandleler.h"

#include"../smpch.h"
#include"../Utils/Logger.h"

glm::mat4 projMat;

MouseHandleler::MouseHandleler(){
	for (int i = 0; i < 3; i++)
		mouseButtons[i] = false;
}

bool MouseHandleler::IsMouseButtonPressed(int button) {
	if (button > MouseHandleler::Get().ArrayLength()) return false;

	return MouseHandleler::Get().mouseButtons[button];
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

glm::vec2 MouseHandleler::GetMousePosModel() {
	return projMat * glm::vec4(position, 1.0f, 1.0f);
}

void MouseHandleler::GetProjectionMatrix(glm::mat4& _projMat) {
	projMat = _projMat;
}

void MouseHandleler::DebugCheckMouesPosAbs() {
	std::stringstream ss;
	ss << "Mouse position  x " << position.x << " mouse position y " << position.y;
	LOGGER_INFO(ss.str());
}

void MouseHandleler::DebugCheckMousePosModel() {
}

