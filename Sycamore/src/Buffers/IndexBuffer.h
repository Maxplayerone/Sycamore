#pragma once

class IndexBuffer {
private:
	unsigned int m_BufferID;
	unsigned int m_indiciesCount;

	void CreateIndexBuffer(const void* indiciesPointer);
public:
	IndexBuffer(unsigned int indeciesCount);
	~IndexBuffer();
	void Bind();
	void Unbind();
	unsigned int GetCount() { return m_indiciesCount; }
};


