#pragma once
#include"../Shadering/Texture.h"

#include"Sprite.h"

#include<vector>

class SpriteSheet {
private:
	Texture* m_texture;
	std::vector<Sprite*> m_sprites;
public:

	SpriteSheet(Texture* texture, unsigned int spriteHeight, unsigned int spriteWidth, unsigned int numOfSprites, unsigned int spacing) {
		m_texture = texture;

		//left-top of the spriteSheet
		int currentX = 0;
		int currentY = texture->GetHeight() - spriteHeight;

		for (int i = 0; i < numOfSprites; i++) {
			//resizing the sprites coordinates to 0.0f-1.0f ratio
			float topY = (currentY + spriteHeight) / (float)texture->GetHeight();
			float rightX = (currentX + spriteWidth) / (float)texture->GetWidth();
			float leftX = currentX / (float)texture->GetWidth();
			float bottomY = currentY / (float)texture->GetHeight();

			float texCoords[8] = {
				leftX, bottomY,
				rightX, bottomY,
				leftX, topY,
				rightX, topY
			};

			Sprite* sprite = new Sprite(m_texture, texCoords);
			m_sprites.push_back(sprite);

			currentX += (spriteWidth + spacing);
			if (currentX >= texture->GetWidth()) {
				currentX = 0;
				currentY -= spriteHeight + spacing;
			}
		}
	}

	SpriteSheet() : m_texture() {}

	Sprite* GetSprite(unsigned int index) {
		return m_sprites[index];
	}
};
