#include"AssetsPool.h"

AssetsPool AssetsPool::_instance;

Shader* AssetsPool::GetShader(const std::string& filepath) {
	auto itr = shaders.find(filepath);
	if (itr != shaders.end()) return itr->second;

	Shader* tempShader = new Shader(filepath);
	shaders.insert(std::make_pair(filepath, tempShader));
	currentShader = tempShader;
	return tempShader;
}

Texture* AssetsPool::GetTexture(const std::string& filepath) {
	auto itr = textures.find(filepath);
	if (itr != textures.end()) return itr->second;

	if (textureIndex >= 8) {
		std::cout << "Texture slots are full!" << std::endl;
		ASSERT(false);
	}

	Texture* tempTex = new Texture(filepath, textureIndex++);
	textures.insert(std::make_pair(filepath, tempTex));
	currentShader->SetUniform1iv("u_Textures");
	return tempTex;
}

SpriteSheet* AssetsPool::GetSpriteSheet(Texture* texture, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing) {
	auto itr = spriteSheets.find(texture);
	if (itr != spriteSheets.end()) return itr->second;

	SpriteSheet* spriteSheet = new SpriteSheet(texture, spriteHeight, spriteWidth, numOfSprites, spacing);
	spriteSheets.insert(std::make_pair(texture, spriteSheet));

	return spriteSheet;
}

SpriteSheet* AssetsPool::GetSpriteSheet(Texture* texture, unsigned int spriteLength, unsigned int numOfSprites) {
	auto itr = spriteSheets.find(texture);
	if (itr != spriteSheets.end()) return itr->second;

	SpriteSheet* spriteSheet = new SpriteSheet(texture, spriteLength, spriteLength, numOfSprites, 0);
	spriteSheets.insert(std::make_pair(texture, spriteSheet));

	return spriteSheet;
}
