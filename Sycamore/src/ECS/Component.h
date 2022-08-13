#pragma once
#include"../Utils/DataTypes.h"

#include"imgui/imgui.h"
#include"../../Math/SM_math.h"

class Component {
public:

	void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void ImGui() {};
};
