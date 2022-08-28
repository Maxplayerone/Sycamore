#include"Framebuffer.h"

#include"../Utils/DataTypes.h"
#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"

#include"GL/glew.h"
/*
struct FramebufferData {
	uint fboID = -1;
	uint colorAttachment;
	uint depthAttachment;
};
*/

FramebufferData SM_Buffers::CreateFramebuffer(uint width, uint height) {
	FramebufferData data;

	glCreateFramebuffers(1, &data.fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, data.fboID);

	glCreateTextures(GL_TEXTURE_2D, 1, &data.colorAttachment);
	glBindTexture(GL_TEXTURE_2D, data.colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, data.colorAttachment, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &data.depthAttachment);
	glBindTexture(GL_TEXTURE_2D, data.depthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0,
	// 	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, data.depthAttachment, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOGGER_ERROR("The framebuffer is not complete");
		ASSERT(false);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return data;
}

void SM_Buffers::BindFramebuffer(uint id) {
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void SM_Buffers::UnbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}