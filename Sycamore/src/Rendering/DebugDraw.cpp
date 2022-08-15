#include"DebugDraw.h"

#include"../smpch.h"

#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"
#include"../Buffers/VertexBuffer.h"
#include"../Buffers/VertexBufferLayout.h"

#include"../Utils/AssetsPool.h"
#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"

const unsigned int MAX_DEBUG_OBJECTS = 50;
//(2 * position + 3 * colours) * 2
const unsigned int VERTEX_PER_OBJECT = 10;
float vertices[MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT];

//should be changed to true if we added an object
//we need to re-setup the buffers
//because we added data to vertices array
bool dirty = false;


struct DebugLine2D {
	SM_math::vec2 start;
	SM_math::vec2 end;
	color3 color;
	float lifetime;
};

unsigned int debugLine2DCount = 0;
DebugLine2D lines2D[MAX_DEBUG_OBJECTS];

void PrintLine2D(unsigned int arrayIndex) {
	std::stringstream ss;
	DebugLine2D line = lines2D[arrayIndex];

	ss << "Start vector: " << line.start << "\0";
	ss << "End vector: " << line.end << "\0";
	ss << "Color: " << line.color << "\0";
	ss << "Lifetime: " << line.lifetime << "\0";

	LOGGER_INFO(ss.str());
}

void UpdateVerticesLine2D() {
	DebugLine2D newLine = lines2D[debugLine2DCount];
	float xValue = newLine.start.x;
	float yValue = newLine.start.y;

	for (int i = 0; i < 2; i++) {
		switch (i) {
		case 1:
			xValue = newLine.end.x;
			yValue = newLine.end.y;
			break;
		}

		//that 5 is a number of unique vertex data (aka 2 * position and 3 * color)
		vertices[(i * 5) + (debugLine2DCount * VERTEX_PER_OBJECT + 0)] = xValue;
		vertices[(i * 5) + (debugLine2DCount * VERTEX_PER_OBJECT + 1)] = yValue;
		vertices[(i * 5) + (debugLine2DCount * VERTEX_PER_OBJECT + 2)] = newLine.color.r;
		vertices[(i * 5) + (debugLine2DCount * VERTEX_PER_OBJECT + 3)] = newLine.color.g;
		vertices[(i * 5) + (debugLine2DCount * VERTEX_PER_OBJECT + 4)] = newLine.color.b;
	}

	debugLine2DCount++;
	dirty = true;
}

//deletes an object from the vertices array by changing it's values to 0
void DeleteFromVertices(unsigned int arrayIndex) {
	//made specifically for lines
	for (int i = 0; i < VERTEX_PER_OBJECT * 2; i++) {
		vertices[arrayIndex + i] = 0;
	}
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime) {
	DebugLine2D tmpLine;
	tmpLine.start = start;
	tmpLine.end = end;
	tmpLine.color = color;
	tmpLine.lifetime = lifetime;
	lines2D[debugLine2DCount] = tmpLine;

	UpdateVerticesLine2D();
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime) {
	DebugDraw::AddLine2D(start, end, {1.0f, 1.0f, 1.0f}, lifetime);
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end) {
	DebugDraw::AddLine2D(start, end, { 1.0f, 1.0f, 1.0f }, 1.0f);
}

void SetupBuffers() {
	VertexArray* va = new VertexArray();

	VertexBufferLayout vbLayout;
	vbLayout.AddFloat(2); // position
	vbLayout.AddFloat(3); // colour

	VertexBuffer* vb = new VertexBuffer(MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT * sizeof(float), vertices);
	va->AddVertexBuffer(*vb, vbLayout);

	GLCall(glLineWidth(1.5f));

	Shader* shader = AssetsPool::Get().GetShader();
	shader->UseProgram();
}

void DebugDraw::Start() {
	SetupBuffers();
}

//checks if any debug object is dead
void UpdateFrame() {

	for (int i = 0; i < debugLine2DCount; i++) {
		lines2D[i].lifetime--;
		if (lines2D[i].lifetime <= 0.0f) {
			DeleteFromVertices(i);
		}
	}
}

void DebugDraw::Render() {
	UpdateFrame();

	if (dirty) {
		SetupBuffers();
		dirty = false;
	}
	
	GLCall(glDrawArrays(GL_LINES, 0, 2));
}


