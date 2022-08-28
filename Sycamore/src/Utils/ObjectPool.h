#pragma once
#include"../smpch.h"

#include"DataTypes.h"

#include"../Rendering/Texture.h"

#include"../ECS/Spritesheet.h"

namespace SM_Pool {
	uint GetShaderID(const std::string& filepath = "src/Assets/Shaders/Shader.shader");
	//relative filepath
	Texture* GetTexture(const std::string& filename);
	uint GetTexIndex();
	void SetTexIndex(uint index);

	SpriteSheet* GetSpriteSheet(const std::string& fileName, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing);
	SpriteSheet* GetSpriteSheet(const std::string& fileName, unsigned int spriteDimensions, unsigned int numOfSprites);

	int GetFramebufferID(uint width, uint height);
	int GetFramebufferColorAttachment();
}