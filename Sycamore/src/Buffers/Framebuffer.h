#pragma once
typedef unsigned int uint;

struct FramebufferData {
	uint fboID = -1;
	uint colorAttachment;
	uint depthAttachment;
};

namespace SM_Buffers {
	FramebufferData CreateFramebuffer(uint width, uint height);

	void BindFramebuffer(uint ID);
	void UnbindFramebuffer();
}