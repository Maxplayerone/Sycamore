#pragma once
#include"../../vendor/imGui/imgui.h"
#include"../../vendor/imGui/imgui_impl_glfw.h"
#include"../../vendor/imGui/imgui_impl_opengl3.h"

class Component {
public:

	void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void ImGui() {};
};
