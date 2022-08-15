#pragma once
#include"../Utils/ErrorHandling.h"
#include"../smpch.h"

struct VertexBufferElements {
	unsigned int type; //the type of the verticies (floats, uint)
	unsigned int count; //the number of data in a single vertex
	unsigned int normalized; //if the vertex should be normalized to screen view

	static unsigned int GetTypeInBytes(unsigned int type) {
		switch (type) {
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	unsigned int m_Stride;
	std::vector<VertexBufferElements> m_Elements;

	void Push(unsigned int type, unsigned int count, unsigned char normalized) {
		m_Elements.push_back({ type, count, normalized });
		m_Stride += count * VertexBufferElements::GetTypeInBytes(type);
	}
public:
	VertexBufferLayout() : m_Stride(0) {}

	void AddFloat(unsigned int count) { Push(GL_FLOAT, count, GL_FALSE); }
	void AddUnsignedInt(unsigned int count) { Push(GL_UNSIGNED_INT, count, GL_FALSE); }
	inline const std::vector<VertexBufferElements> GetElements() const { return m_Elements; }
	//returns the offset of vertex
	inline unsigned int GetStride() const { return m_Stride; }
};

