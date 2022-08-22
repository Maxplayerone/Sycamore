#pragma once
#include"../Utils/DataTypes.h"

namespace SM_Buffers {
		uint CreateVertexBuffer(unsigned int bufferSizeBytes, const void* vertexDataPointer);
		void DestroyVertexBuffer(uint id);

		void BindVertexBuffer(uint id);
		void UnbindVertexBuffer();
}


