#pragma once
#include"Component.h"
#include"Sprite.h"
#include"GameObject.h"
#include"Spritesheet.h"

#include"../Utils/DataTypes.h"

class SpriteRenderer : public Component {
private:
	unsigned int m_TextureIndex;
	Sprite* m_Sprite;

	color4 color;

	bool dirty;

	bool hasTexture;

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

	SpriteRenderer(color4 _color) {
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		color.a = _color.a;

		m_Sprite = GetDummySprite();
		m_TextureIndex = 0;

		dirty = true;
		hasTexture = false;
	}

	SpriteRenderer(Sprite* sprite) {
		color.r = 1.0f;
		color.g = 1.0f;
		color.b = 1.0f;
		color.a = 1.0f;

		m_Sprite = sprite;
		m_TextureIndex = sprite->GetTexSlot();

		dirty = true;
		hasTexture = true;
	}

	SpriteRenderer(Texture* tex) {
		color.r = 1.0f;
		color.g = 1.0f;
		color.b = 1.0f;
		color.a = 1.0f;


		m_TextureIndex = tex->GetSlot();
		m_Sprite = GetDummySprite();

		dirty = true;
		hasTexture = true;
	}

	SpriteRenderer(SpriteSheet* sheet, uint spriteIndex) {
		color.r = 1.0f;
		color.g = 1.0f;
		color.b = 1.0f;
		color.a = 1.0f;

		m_TextureIndex = sheet->GetSprite(spriteIndex)->GetTexSlot();
		m_Sprite = sheet->GetSprite(spriteIndex);

		dirty = true;
		hasTexture = true;
	}

	unsigned int GetTexIndex() const { return m_TextureIndex; }
	float* GetTexCoords() const { return m_Sprite->GetTexCoords(); }
	Texture* GetTexture() const { return m_Sprite->GetTexture(); }
	bool HasTexture() const { return hasTexture; }
	color4 GetColor4() const { return color; }

	Sprite* GetSprite() const { return m_Sprite; }

	void SetColor4(color4 _color) {
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		color.a = _color.a;

		dirty = true;
	}

	void SetSprite(Sprite* _sprite) {
		m_Sprite = _sprite;
		dirty = true;
	}

	void Clean() { dirty = false; }

	bool IsDirty() { return dirty; }

	void Update(float deltaTime) override {
	}

	//only works for colors
	void ImGui() override {
		color4 oldColor = color;

		ImGui::Begin("Sprite renderer");
		ImGui::SliderFloat("Red", &color.r, 0.0f, 1.0f);
		ImGui::SliderFloat("Green", &color.g, 0.0f, 1.0f);
		ImGui::SliderFloat("Blue", &color.b, 0.0f, 1.0f);
		ImGui::SliderFloat("Alpha", &color.a, 0.0f, 1.0f);

		if (color.r != oldColor.r || color.g != oldColor.g || color.b != oldColor.b || color.a != oldColor.a)
			dirty = true;

		ImGui::End();
	}
};
