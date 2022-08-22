#pragma once

typedef unsigned int uint;

namespace SM_Buffers {
	uint CreateIndexBuffer(int indiciesCount);
	void DeleteIndexBuffer(uint id);

	void BindIndexBuffer(uint id);
	void UnbindIndexBuffer();
}


