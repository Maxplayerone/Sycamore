#include"VertexArray.h"

#include"VertexBufferLayout.h"
#include"VertexBuffer.h"

uint arrayBufferID;

uint SM_Buffers::CreateVertexArray() {
	GLCall(glGenVertexArrays(1, &arrayBufferID));
	GLCall(glBindVertexArray(arrayBufferID));

	return arrayBufferID;
}

void SM_Buffers::BindVertexArray(uint id){
	GLCall(glBindVertexArray(id));
}


void SM_Buffers::UnbindVertexArray(){
	GLCall(glBindVertexArray(0));
}

void SM_Buffers::DeleteVertexArray(uint id) {
	GLCall(glDeleteVertexArrays(1, &id));
}

void SM_Buffers::AddVertexBuffer(uint vaID, uint vbID, const VertexBufferLayout& layout) {
	BindVertexArray(vaID);
	SM_Buffers::BindVertexBuffer(vbID);
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