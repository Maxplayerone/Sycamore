#include"ObjectPool.h"

#include"Logger.h"
#include"ErrorHandling.h"
#include"DataTypes.h"

#include"../Rendering/Shader.h"

#include"../Buffers/Framebuffer.h"

#define SHADER_ARRAY_SIZE 8

struct shaderInfo {
	std::string filepath;
	uint id;
};
shaderInfo shaders[SHADER_ARRAY_SIZE];
int shaderIndex = 0;

//(used mostly to find already in-use ID's)
//returns an index for found item or -1 if the item is not found
int FindShader(std::string searchingItem) {
	for (int i = 0; i < shaderIndex; i++) {
		if ((searchingItem.compare(shaders[i].filepath)) == 0) {
			return i;
		}
	}
	return -1;
}

uint SM_Pool::GetShaderID(const std::string& filepath) {
	int itemIndex = FindShader(filepath);

	//item is in the array
	if (itemIndex > -1) return shaders[itemIndex].id;

	uint newShader = Shader::CreateShader(filepath);
	shaders[shaderIndex].filepath = filepath;
	shaders[shaderIndex].id = newShader;
	shaderIndex++;

	return newShader;
}


std::unordered_map<std::string, Texture*> textures;
uint textureIndex = 1;

Texture* SM_Pool::GetTexture(const std::string& fileName) {
	std::stringstream ss;
	ss << "src/Assets/Images/" << fileName;
	std::string filepath = ss.str();

	auto itr = textures.find(filepath);
	if (itr != textures.end()) return itr->second;

	if (textureIndex >= 8) {
		LOGGER_ERROR("Texture slots are full");
		ASSERT(false);
	}

	Texture* tempTex = new Texture(filepath, textureIndex++);
	textures.insert(std::make_pair(filepath, tempTex));

	uint shaderID = SM_Pool::GetShaderID();
	Shader::SetUniform1iv(shaderID, "u_Textures");
	return tempTex;
}

uint SM_Pool::GetTexIndex() {
	return textureIndex;
}

void SM_Pool::SetTexIndex(uint index) {
	textureIndex = index;
}

std::unordered_map<Texture*, SpriteSheet*> spriteSheets;

SpriteSheet* SM_Pool::GetSpriteSheet(const std::string& fileName, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing) {
	
	Texture* texture = GetTexture(fileName);

	auto itr = spriteSheets.find(texture);
	if (itr != spriteSheets.end()) return itr->second;

	SpriteSheet* spriteSheet = new SpriteSheet(texture, spriteHeight, spriteWidth, numOfSprites, spacing);
	spriteSheets.insert(std::make_pair(texture, spriteSheet));

	return spriteSheet;
}

SpriteSheet* SM_Pool::GetSpriteSheet(const std::string& fileName, unsigned int spriteDimensions, unsigned int numOfSprites) {
	
	Texture* texture = GetTexture(fileName);

	auto itr = spriteSheets.find(texture);
	if (itr != spriteSheets.end()) return itr->second;

	SpriteSheet* spriteSheet = new SpriteSheet(texture, spriteDimensions, spriteDimensions, numOfSprites, 0);
	spriteSheets.insert(std::make_pair(texture, spriteSheet));

	return spriteSheet;
}

//In my implementation there can only be one framebuffer
//change it if you need it yo

FramebufferData fboData;
bool fboRegistered = false;

int SM_Pool::GetFramebufferID(uint width, uint height) {
	if (fboRegistered) return fboData.fboID;

	fboData = SM_Buffers::CreateFramebuffer(width, height);
	fboRegistered = true;
	return fboData.fboID;
}

int SM_Pool::GetFramebufferColorAttachment() {
	if (!fboRegistered) {
		LOGGER_WARNING("The framebuffer is not initialized yet (Use GetFramebufferID method to initialize it");
		return - 1;
	}

	return fboData.colorAttachment;
}