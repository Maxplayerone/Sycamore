#include"VertexBuffer.h"
#include<array>

VertexBuffer::VertexBuffer(unsigned int bufferSize, const void* vertexDataPointer) {
	GLCall(glGenBuffers(1, &m_BufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexDataPointer, GL_STATIC_DRAW));
}


void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

void VertexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_BufferID));
}
