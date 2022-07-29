#pragma once
#include"../Shadering/Texture.h"

class Sprite {
private:
	Texture* m_texture;
	float m_TexCoords[8];

public:
	Sprite(Texture* _texture)
		: m_texture(_texture)
	{
		float leftX = 0.0f;
		float rightX = m_texture->GetWidth();
		float topY = m_texture->GetHeight();
		float bottomY = 0.0f;

		m_TexCoords[0] = leftX;
		m_TexCoords[1] = bottomY;
		m_TexCoords[2] = rightX;
		m_TexCoords[3] = bottomY;
		m_TexCoords[4] = leftX;
		m_TexCoords[5] = topY;
		m_TexCoords[6] = rightX;
		m_TexCoords[7] = topY;
	}

	Sprite(Texture* _texture, float texCoords[8]) {
		m_texture = _texture;
		for (int i = 0; i < 8; i++) {
			m_TexCoords[i] = texCoords[i];
		}
	}

	Sprite(float texCoords[8]) {
		m_texture = nullptr;
		for (int i = 0; i < 8; i++) {
			m_TexCoords[i] = texCoords[i];
		}
	}

	float* GetTexCoords() { return m_TexCoords; }
	Texture* GetTexture() const { if (m_texture != nullptr) return m_texture; }
	unsigned int GetTexSlot() const { return m_texture->GetSlot(); }
};

