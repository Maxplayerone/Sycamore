#pragma once
#include"../smpch.h"

#include"DataTypes.h"

#include"../Rendering/Texture.h"

#include"../ECS/Spritesheet.h"

namespace SM_Pool {

	int GetShader(const std::string& filename = "main.shader");

	Texture* GetTexture(const std::string& filepath);
	uint GetTexIndex();

	SpriteSheet* GetSpriteSheet(const std::string& filepath, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing);
	SpriteSheet* GetSpriteSheet(const std::string& filepath, unsigned int spriteDimensions, unsigned int numOfSprites);

	int GetFramebufferID(uint width, uint height);
	int GetFramebufferColorAttachment();
}