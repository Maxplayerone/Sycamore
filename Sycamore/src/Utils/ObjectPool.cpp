#include"ObjectPool.h"

#include"Logger.h"
#include"ErrorHandling.h"
#include"DataTypes.h"

#include"../Rendering/Shader.h"

#include"../Buffers/Framebuffer.h"

std::unordered_map<std::string, uint> shaders;

int SM_Pool::GetShader(const std::string& filename){
	auto itr = shaders.find(filename);
	if (itr != shaders.end()) return itr->second;

	int id = Shader::CreateShader(filename, 420);
	shaders.insert(std::make_pair(filename, id));
	return id;
}

std::unordered_map<std::string, Texture*> textures;
uint textureIndex = 1;

Texture* SM_Pool::GetTexture(const std::string& filepath) {
	//std::stringstream ss;
	//ss << "src/Assets/Images/" << fileName;
	//std::string filepath = ss.str();

	auto itr = textures.find(filepath);
	if (itr != textures.end()) return itr->second;

	if (textureIndex >= 8) {
		LOGGER_ERROR("Texture slots are full");
		ASSERT(false);
	}

	Texture* tempTex = new Texture(filepath, textureIndex++);
	textures.insert(std::make_pair(filepath, tempTex));

	//we use the main shader because it's the only one who uses textures
	uint id = SM_Pool::GetShader();
	Shader::SetUniform1iv(id, "u_Textures");
	return tempTex;
}

uint SM_Pool::GetTexIndex() {
	return textureIndex;
}

std::unordered_map<Texture*, SpriteSheet*> spriteSheets;

SpriteSheet* SM_Pool::GetSpriteSheet(const std::string& filepath, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int numOfSprites, unsigned int spacing) {
	
	Texture* texture = GetTexture(filepath);

	auto itr = spriteSheets.find(texture);
	if (itr != spriteSheets.end()) return itr->second;

	SpriteSheet* spriteSheet = new SpriteSheet(texture, spriteHeight, spriteWidth, numOfSprites, spacing);
	spriteSheets.insert(std::make_pair(texture, spriteSheet));

	return spriteSheet;
}

SpriteSheet* SM_Pool::GetSpriteSheet(const std::string& filepath, unsigned int spriteDimensions, unsigned int numOfSprites) {
	
	Texture* texture = GetTexture(filepath);

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


int gameObjectIDCount = -1;
int SM_Pool::GetGameObjectID() {
	gameObjectIDCount += 1;
	return gameObjectIDCount;
}