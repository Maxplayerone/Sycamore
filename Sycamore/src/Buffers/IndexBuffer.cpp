#include"IndexBuffer.h"
#include"../Utils/ErrorHandling.h"

uint IndexbufferID;

uint SM_Buffers::CreateIndexBuffer(int indiciesCount) {

    uint* indices = new unsigned int[indiciesCount];
    uint numOfQuads = indiciesCount / 6;

    for (int i = 0; i < numOfQuads; i++) {
        //LB, RB, RT, RT, LT, LB
        indices[0 + (i * 6)] = 0 + (i * 4);
        indices[1 + (i * 6)] = 1 + (i * 4);
        indices[2 + (i * 6)] = 3 + (i * 4);
        indices[3 + (i * 6)] = 3 + (i * 4);
        indices[4 + (i * 6)] = 2 + (i * 4);
        indices[5 + (i * 6)] = 0 + (i * 4);
    }

    GLCall(glGenBuffers(1, &IndexbufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexbufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indiciesCount, (void*)indices, GL_STATIC_DRAW));

    delete[] indices;
    return IndexbufferID;
}

void SM_Buffers::DeleteIndexBuffer(uint id) {
    glDeleteBuffers(1, &id);
}

void SM_Buffers::BindIndexBuffer(uint id) {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void SM_Buffers::UnbindIndexBuffer() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
