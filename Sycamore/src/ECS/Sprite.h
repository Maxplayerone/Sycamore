#pragma once
#include"../Rendering/Texture.h"

class Sprite {
private:
	Texture* m_texture;
	float m_TexCoords[8];

	//it's used to 1) know if the sprite comes from the spritesheet
	//and 2) to know on which index the sprite is the the sheet
	int spritesheetIndex = -1;

public:
	Sprite(Texture* _texture)
		: m_texture(_texture)
	{
		float leftX = 0.0f;
		float rightX = m_texture->GetWidth();
		float topY = m_texture->GetHeight();
		float bottomY = 0.0f;
		/*
		m_TexCoords[0] = leftX;
		m_TexCoords[1] = bottomY;
		m_TexCoords[2] = rightX;
		m_TexCoords[3] = bottomY;
		m_TexCoords[4] = leftX;
		m_TexCoords[5] = topY;
		m_TexCoords[6] = rightX;
		m_TexCoords[7] = topY;
		*/

		m_TexCoords[0] = 0.0f;
		m_TexCoords[1] = 0.0f;

		m_TexCoords[2] = 1.0f;
		m_TexCoords[3] = 0.0f;

		m_TexCoords[4] = 0.0f;
		m_TexCoords[5] = 1.0f;

		m_TexCoords[6] = 1.0f;
		m_TexCoords[7] = 1.0f;
	}

	Sprite(Texture* _texture, float texCoords[8]) {
		m_texture = _texture;
		for (int i = 0; i < 8; i++) {
			m_TexCoords[i] = texCoords[i];
		}
	}

	//used in spriteRenderer when we make an object than has color and no texture
	Sprite() {
		m_texture = nullptr;

		m_TexCoords[0] = 0;
		m_TexCoords[1] = 0;
		m_TexCoords[2] = 1;
		m_TexCoords[3] = 0;
		m_TexCoords[4] = 0;
		m_TexCoords[5] = 1;
		m_TexCoords[6] = 1;
		m_TexCoords[7] = 1;
	}

	float* GetTexCoords() { return m_TexCoords; }
	Texture* GetTexture() const { if (m_texture != nullptr) return m_texture; }
	unsigned int GetTexSlot() const { if (m_texture == nullptr) return 0; else return m_texture->GetSlot();  }

	void SetSpritesheetIndex(int index) { spritesheetIndex = index; }
	int GetSpritesheetIndex() const { return spritesheetIndex; }
};

