#include"Texture.h"

#include"../../STBI_IMAGE/stbi_image.h"

#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"
#include"../Utils/ObjectPool.h"

Texture::Texture(const std::string& path)
	: m_TextureID(0), m_FilePath(path), m_imageBuffer(nullptr),
	m_width(0), m_height(0), m_channels(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_imageBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
	if (!m_imageBuffer) {
		std::stringstream ss;
		ss << "Cannot load the texture file from the filepath " << path;
		LOGGER_ERROR(ss.str());
		ASSERT(false);
	}

	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, m_imageBuffer));

	Unbind();
	if (m_imageBuffer)
		stbi_image_free(m_imageBuffer);
}

Texture::Texture(const std::string& path, unsigned int slot)
	: m_TextureID(0), m_FilePath(path), m_imageBuffer(nullptr),
	m_width(0), m_height(0), m_channels(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_imageBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
	if (!m_imageBuffer) {
		std::stringstream ss;
		ss << "Cannot load the texture file from the filepath " << path;
		LOGGER_ERROR(ss.str());
		ASSERT(false);
	}

	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, m_imageBuffer));

	Unbind();
	if (m_imageBuffer)
		stbi_image_free(m_imageBuffer);

	AssignTextureSlot(slot);
}


Texture::~Texture() {
	GLCall(glDeleteTextures(1, &m_TextureID));
}

void Texture::Bind() const {
	if (m_slot == 0) {
		LOGGER_WARNING("You haven't assigned a texture slot");
		return;
	}
	GLCall(glActiveTexture(GL_TEXTURE0 + m_slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::Unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::AssignTextureSlot(unsigned int slot) {
	m_slot = slot;
	GLCall(glBindTextureUnit(slot, m_TextureID));
}

