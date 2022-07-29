#pragma once
#include"Component.h"

class Transform : public Component {
private:
	bool dirty;
	float positions[2];
public:

	Transform(float posX, float posY) {
		dirty = false;
		positions[0] = posX;
		positions[1] = posY;
	}

	void Update(float deltaTime) override {
		//std::cout << "Updating transform" << std::endl;
	}

	void SetPosition(float x, float y) {
		this->positions[0] = x;
		this->positions[1] = y;
		dirty = true;
	}

	bool IsDirty() { return dirty; }
	float GetPos(unsigned int index) { return positions[index]; }

	void ImGui() override {
		ImGui::Begin("Transform");
		ImGui::SliderFloat2("Position", positions, -2.0f, 2.0f);
		std::cout << "x " << positions[0] << " y " << positions[1] << std::endl;
		dirty = true;
		ImGui::End();
	}
};