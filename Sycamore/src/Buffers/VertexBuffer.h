#pragma once

class VertexBuffer {
private:
	unsigned int m_BufferID;
public:
	VertexBuffer(unsigned int bufferSizeBytes, const void* vertexDataPointer);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};


