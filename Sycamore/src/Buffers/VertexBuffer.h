#pragma once
#include"../Utils/ErrorHandling.h"

class VertexBuffer {
private:
	unsigned int m_BufferID;
public:
	VertexBuffer(unsigned int bufferSize, const void* vertexDataPointer);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};


