#include"VertexBuffer.h"

#include"../Utils/ErrorHandling.h"

uint bufferID;

uint SM_Buffers::CreateVertexBuffer(unsigned int bufferSizeBytes, const void* vertexDataPointer) {
	GLCall(glGenBuffers(1, &bufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, bufferSizeBytes, vertexDataPointer, GL_DYNAMIC_DRAW));

	return bufferID;
}



void SM_Buffers::BindVertexBuffer(uint id) {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void SM_Buffers::UnbindVertexBuffer(){
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void SM_Buffers::DestroyVertexBuffer(uint id) {
	GLCall(glDeleteBuffers(1, &id));
}
