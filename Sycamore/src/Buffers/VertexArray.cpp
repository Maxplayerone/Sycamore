#include"VertexArray.h"

#include"VertexBufferLayout.h"
#include"VertexBuffer.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_BufferID));
	GLCall(glBindVertexArray(m_BufferID));
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_BufferID));
}


void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_BufferID));
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElements>& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const VertexBufferElements& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
			layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElements::GetTypeInBytes(element.type);
	}
}