#pragma once
#include"../smpch.h"

class Texture {
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_imageBuffer;
	int m_width, m_height, m_channels;

	unsigned int m_slot;

	//assignes a texture slot to a particlular texture
	void AssignTextureSlot(unsigned int slot);
public:
	Texture(const std::string& path);
	Texture(const std::string& path, unsigned int slot);

	~Texture();

	void Bind() const;
	void Unbind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	unsigned int GetSlot() const { return m_slot; }
	Texture* GetTexture() { return this; }
};
