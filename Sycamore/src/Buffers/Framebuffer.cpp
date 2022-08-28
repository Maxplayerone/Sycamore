#include"Framebuffer.h"

#include"../Utils/DataTypes.h"
#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"

#include"GL/glew.h"

#include"../Rendering/Texture.h"

/*
struct FramebufferData {
	uint fboID = -1;
	uint rboID = -1;

	Texture* tex;
};
*/

FramebufferData SM_Buffers::CreateFramebuffer(uint width, uint height) {
	FramebufferData data;
	
	//framebuffer- a struct for buffers and textures
	GLCall(glGenFramebuffers(1, &data.fboID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, data.fboID));

	data.tex = new Texture(width, height);
	//joins the framebuffer with the texture
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, data.tex->GetOpenGLTexID(), 0));

	GLCall(glGenRenderbuffers(1, &data.rboID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, data.rboID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height));
	//adds the renderbuffer to framebuffer as a depth attachment
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, data.rboID));

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOGGER_ERROR("The framebuffer is not complete");
		ASSERT(false);
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return data;
}

/*
void OpenGLFramebuffer::Invalidate()
	{
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0,
		// 	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		HZ_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
*/

void SM_Buffers::BindFramebuffer(uint id) {
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void SM_Buffers::UnbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}