#pragma once
#include"Component.h"

class Transform : public Component {
private:
	bool dirty;

	SM_math::vec2 pos;
	SM_math::vec2 radius;

public:

	//position x and position y
	Transform(SM_math::vec2 _pos) {
		dirty = true;
		pos.x = _pos.x;
		pos.y = _pos.y;

		radius.x = 16.0f;
		radius.y = 16.0f;
	}

	Transform(SM_math::vec2 _pos, SM_math::vec2 _radius) {
		dirty = true;
		pos.x = _pos.x;
		pos.y = _pos.y;

		radius.x = _radius.x;
		radius.y = _radius.y;
	}

	Transform(SM_math::vec2 _pos, float r) {
		dirty = true;
		pos.x = _pos.x;
		pos.y = _pos.y;

		radius.x = r;
		radius.y = r;
	}

	void Update(float deltaTime) override {
		//std::cout << "Updating transform" << std::endl;
	}

	void SetPosition(SM_math::vec2 _pos) {
		pos.x = _pos.x;
		pos.y = _pos.y;
		dirty = true;
	}

	void SetRadius(SM_math::vec2& r) {
		radius = r;
		dirty = true;
	}

	bool IsDirty() const { return dirty; }
	void Clean() { dirty = false; }

	SM_math::vec2 GetPos() const { return pos; }
	SM_math::vec2 GetRadius() const { return radius; }

	void ImGui() override {
		float lastPosX = pos.x;
		float lastPosY = pos.y;
		float lastScaleX = radius.x;
		float lastScaleY = radius.y;

		ImGui::Begin("Transform");
		ImGui::SliderFloat("Position x", &pos.x, -480.0f, (480.0f - radius.x));
		ImGui::SliderFloat("Position y", &pos.y, -320.0f, 320.0f);

		//for now I just care about having nice, symetrical quads
		ImGui::SliderFloat("Scale", &radius.x, -100.0f, 100.0f);
		radius.y = radius.x;

		//checking for dirty flag
		if (pos.x != lastPosX || pos.y != lastPosY || radius.x != lastScaleX || radius.y != lastScaleY)
			dirty = true;

		ImGui::End();
	}
};