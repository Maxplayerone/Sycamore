#include"IndexBuffer.h"
#include"../Utils/ErrorHandling.h"

IndexBuffer::IndexBuffer(unsigned int indeciesCount)
    : m_indiciesCount(indeciesCount), m_BufferID(0) {

    unsigned int* indices = new unsigned int[indeciesCount];

    unsigned int numOfQuads = indeciesCount / 6;
    unsigned int offset = 4;

    for (int i = 0; i < numOfQuads; i++) {
        //LB, RB, RT, RT, LT, LB
        indices[0 + (i * 6)] = 0 + (i * offset);
        indices[1 + (i * 6)] = 1 + (i * offset);
        indices[2 + (i * 6)] = 3 + (i * offset);
        indices[3 + (i * 6)] = 3 + (i * offset);
        indices[4 + (i * 6)] = 2 + (i * offset);
        indices[5 + (i * 6)] = 0 + (i * offset);
    }

    CreateIndexBuffer(indices);
}

void IndexBuffer::CreateIndexBuffer(const void* indiciesPointer) {
    GLCall(glGenBuffers(1, &m_BufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indiciesCount, indiciesPointer, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_BufferID);
}

void IndexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::Unbind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}
