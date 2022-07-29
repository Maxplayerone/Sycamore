#pragma once
#include"Component.h"
#include"Sprite.h"
#include"GameObject.h"

class SpriteRenderer : public Component {
private:
	unsigned int m_TextureIndex;
	Sprite* m_Sprite;

	float r;
	float b;
	float g;
	float a;

	bool dirty = false;

	Sprite* GetDummySprite() {
		float texCoords[8] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};
		return new Sprite(texCoords);
	}
public:

	SpriteRenderer(float _r, float _g, float _b, float _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;

		m_Sprite = GetDummySprite();
		m_TextureIndex = 0;
	}

	SpriteRenderer(Sprite* sprite) {
		r = 1.0f;
		b = 1.0f;
		g = 1.0f;
		a = 1.0f;

		m_Sprite = sprite;
		m_TextureIndex = sprite->GetTexSlot();
	}

	SpriteRenderer(unsigned int texIndex) {
		r = 1.0f;
		b = 1.0f;
		g = 1.0f;
		a = 1.0f;


		m_TextureIndex = texIndex;
		m_Sprite = GetDummySprite();
	}

	unsigned int GetTexIndex() const { return m_TextureIndex; }
	float* GetTexCoords() const { return m_Sprite->GetTexCoords(); }
	Texture* GetTexture() const { return m_Sprite->GetTexture(); }
	float GetR() const { return r; }
	float GetG() const { return g; }
	float GetB() const { return b; }
	float GetA() const { return a; }

	void SetR(float value) {
		r = value;
		dirty = true;
	}

	void SetG(float value) {
		g = value;
		dirty = true;
	}

	void SetB(float value) {
		b = value;
		dirty = true;
	}

	void SetA(float value) {
		a = value;
		dirty = true;
	}

	void SetSprite(Sprite* _sprite) {
		m_Sprite = _sprite;
		dirty = true;
	}

	void Clean() { dirty = false; }

	bool IsDirty() { return dirty; }


	void Start() {
		dirty = false;
	}

	void Update(float deltaTime) override {
	}

	//only works for colors
	void ImGui() override {
		float colors[4] = { r, g, b, a };
		ImGui::Begin("Sprite renderer");
		ImGui::SliderFloat4("Colors", colors, 0.0f, 1.0f);
		r = colors[0];
		g = colors[1];
		b = colors[2];
		a = colors[3];
		ImGui::End();
	}
};
