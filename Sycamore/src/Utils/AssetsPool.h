#pragma once
#include<unordered_map>

#include"../Shadering/Shader.h"
#include"../Shadering/Texture.h"
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

	Shader* GetShader(const std::string& filepath);
	unsigned int GetGameObjectID() { return gameObjectIndex++; }

	Texture* GetTexture(const std::string& filepath);

	SpriteSheet* GetSpriteSheet(Texture* texture, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing);
	SpriteSheet* GetSpriteSheet(Texture* texture, unsigned int spriteLength, unsigned int numOfSprites);
};


