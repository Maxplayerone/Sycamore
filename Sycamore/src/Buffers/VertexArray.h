#pragma once

typedef unsigned int uint;

class VertexBufferLayout;

namespace SM_Buffers {
	uint CreateVertexArray();
	void DeleteVertexArray(uint id);

	void BindVertexArray(uint id);
	void UnbindVertexArray();

	void AddVertexBuffer(uint vaID, uint vbID, const VertexBufferLayout& layout);
}

