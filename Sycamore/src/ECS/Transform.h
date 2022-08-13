#pragma once
#include"Component.h"

class Transform : public Component {
private:
	bool dirty;

	SM_math::vec2 pos;
	SM_math::vec2 scale;

public:

	//position x and position y
	Transform(SM_math::vec2 _pos) {
		dirty = false;
		pos.x = _pos.x;
		pos.y = _pos.y;

		scale.x = 1.0f;
		scale.y = 1.0f;
	}

	Transform(SM_math::vec2 _pos, SM_math::vec2 _scale) {
		dirty = false;
		pos.x = _pos.x;
		pos.y = _pos.y;

		scale.x = _scale.x;
		scale.y = _scale.y;
	}

	void Update(float deltaTime) override {
		//std::cout << "Updating transform" << std::endl;
	}

	void SetPosition(SM_math::vec2 _pos) {
		pos.x = _pos.x;
		pos.y = _pos.y;
		dirty = true;
	}

	bool IsDirty() const { return dirty; }
	SM_math::vec2 GetPos() const { return pos; }
	SM_math::vec2 GetScale() const { return scale; }

	void ImGui() override {
		ImGui::Begin("Transform");
		ImGui::SliderFloat("Position x", &pos.x, -480.0f, (480.0f - scale.x));
		ImGui::SliderFloat("Position y", &pos.y, -320.0f, 320.0f);

		//for now I just care about having nice, symetrical quads
		ImGui::SliderFloat("Scale", &scale.x, -100.0f, 100.0f);
		scale.y = scale.x;
		dirty = true;

		ImGui::End();
	}
};