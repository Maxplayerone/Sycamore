#pragma once
typedef unsigned int uint;
class Texture;

struct FramebufferData {
	uint fboID = -1;
	uint rboID = -1;

	Texture* tex;
};

namespace SM_Buffers {
	FramebufferData CreateFramebuffer(uint width, uint height);

	void BindFramebuffer(uint ID);
	void UnbindFramebuffer();
}