#pragma once
#include"../smpch.h"

#include"../Rendering/Shader.h"
#include"../Rendering/Texture.h"
#include"../ECS/SpriteSheet.h"

//TODO: MAKE THE SAME THING FOR TEXTURES
class AssetsPool {
private:
	AssetsPool() {};
	static AssetsPool _instance;

	unsigned int gameObjectIndex = 0;
	unsigned int textureIndex = 1;

	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<Texture*, SpriteSheet*> spriteSheets;

	//used to automatically set the texture slot's uniform to the glsl file
	Shader* currentShader = nullptr;
public:
	AssetsPool(const AssetsPool&) = delete;

	static AssetsPool& Get() {
		return _instance;
	}

	Shader* GetShader(const std::string& filepath = "src/Assets/Shaders/Shader.shader");
	unsigned int GetGameObjectID() { return gameObjectIndex++; }

	Texture* GetTexture(const std::string& fileName);

	//if the user has a texture of the spriteSheet
	SpriteSheet* GetSpriteSheet(Texture* texture, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing);
	//SpriteSheet* GetSpriteSheet(Texture* texture, unsigned int spriteLength, unsigned int numOfSprites);

	//if the user just wants to use the file name (the texture is created automatically)
	SpriteSheet* GetSpriteSheet(const std::string& fileName, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing);
	SpriteSheet* GetSpriteSheet(const std::string& fileName, unsigned int spriteLength, unsigned int numOfSprites);
};


