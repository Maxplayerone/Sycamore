#include"DebugDraw.h"

#include"../smpch.h"
#include"../Settings.h"

#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"
#include"../Buffers/VertexBuffer.h"
#include"../Buffers/VertexBufferLayout.h"

#include"../Utils/AssetsPool.h"
#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"
#include"../Utils/DataTypes.h"

const uint MAX_DEBUG_OBJECTS = 50;
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
	bool hasLifetime;
	float lifetime;

	//when the lifetime of the object
	//is 0 then the object is dead
	//and the bool is true
	//(other objects can you it's space
	//in the vertices buffer)
	bool isFree;
};

uint debugLine2DCount = 0;
DebugLine2D lines2D[MAX_DEBUG_OBJECTS];

void PrintLine2D(uint arrayIndex) {
	std::stringstream ss;
	DebugLine2D line = lines2D[arrayIndex];

	//new lines don't work
	ss << "Start vector: " << line.start << '\0';
	ss << "End vector: " << line.end << '\0';
	ss << "Color: " << line.color << '\0';
	ss << "Lifetime: " << line.lifetime << '\0';

	LOGGER_INFO(ss.str());
}

void PrintLine2D(DebugLine2D line) {
	std::stringstream ss;

	//new lines don't work
	ss << "Start vector: " << line.start << std::endl;
	ss << "End vector: " << line.end << std::endl;
	ss << "Color: " << line.color << std::endl;
	ss << "Lifetime: " << line.lifetime << std::endl;

	LOGGER_INFO(ss.str());
}

static uint numOfCycles = 0;
void TestVerticesData(float buffer[], const uint USED_SPACE, uint cyclesBeforeAssertion) {
	for (uint i = 0; i < USED_SPACE; i++) {
		std::stringstream ss;
		ss << i << "'th index: " << buffer[i] << '\0';
		LOGGER_WARNING(ss.str());
	}
	numOfCycles++;
	if(numOfCycles >= cyclesBeforeAssertion)
		ASSERT(false);
}

void UpdateVerticesLine2D() {
	//checking for the first free space for a line
	DebugLine2D newLine;
	uint freeBufferSpaceIndex = -1;
	for (uint i = 0; i < MAX_DEBUG_OBJECTS; i++) {
		if (lines2D[i].isFree == true) {		
			newLine = lines2D[i];
			freeBufferSpaceIndex = i;
			break;
		}
	}

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
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 0)] = xValue;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 1)] = yValue;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 2)] = newLine.color.r;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 3)] = newLine.color.g;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 4)] = newLine.color.b;
	}

	//TestVerticesData(vertices, (debugLine2DCount  + 1) * VERTEX_PER_OBJECT, 2);

	debugLine2DCount++;
	lines2D[freeBufferSpaceIndex].isFree = false;
	dirty = true;
}

void DeleteFromVertices(uint arrayIndex) {
	for (uint i = 0; i < VERTEX_PER_OBJECT; i++) {
		vertices[i + (arrayIndex * VERTEX_PER_OBJECT)] = 0.0f;
	}
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, bool hasLifetime, float lifetime) {
	DebugLine2D tmpLine;
	tmpLine.start = start;
	tmpLine.end = end;
	tmpLine.color = color;
	tmpLine.hasLifetime = hasLifetime;
	tmpLine.lifetime = lifetime;
	tmpLine.isFree = true;
	lines2D[debugLine2DCount] = tmpLine;

	UpdateVerticesLine2D();
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime) {
	AddLine2D(start, end, color, true, lifetime);
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime) {
	DebugDraw::AddLine2D(start, end, {1.0f, 1.0f, 1.0f}, true, lifetime);
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, bool hasLifetime) {
	DebugDraw::AddLine2D(start, end, { 0.0f, 0.0f, 0.0f }, hasLifetime, 1.0f);
}

void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end) {
	DebugDraw::AddLine2D(start, end, { 0.0f, 0.0f, 0.0f }, false, 1.0f);
}

void SetupBuffers() {
	VertexArray* va = new VertexArray();

	VertexBufferLayout vbLayout;
	vbLayout.AddFloat(2); // position
	vbLayout.AddFloat(3); // colour

	VertexBuffer* vb = new VertexBuffer(MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT * sizeof(float), vertices);
	va->AddVertexBuffer(*vb, vbLayout);

	GLCall(glLineWidth(1.0f));

	Shader* shader = AssetsPool::Get().GetShader();
	shader->UseProgram();
}

void DebugDraw::Start() {
	SetupBuffers();
}


//checks if any debug object is dead
void UpdateFrame() {

	for (uint i = 0; i < debugLine2DCount; i++) {
		if (lines2D[i].isFree) continue;

		if(lines2D[i].hasLifetime)
			lines2D[i].lifetime--;

		if ((lines2D[i].lifetime <= 0.0f)) {
			DeleteFromVertices(i);
			lines2D[i].isFree = true;
		}
	}
}

void DebugDraw::Render() {
	UpdateFrame();
	
	//quick fix for now. Should probably fix it pretty soon
	SetupBuffers();

	//PrintLine2D(0);
	
	GLCall(glDrawArrays(GL_LINES, 0, 2 * debugLine2DCount));
}

//variables for drawDebugGrid method
const int GRID_WIDTH = 32;
const int GRID_HEIGHT = 32;

const int SCREEN_WIDTH = SM_settings::windowWidth;
const int SCREEN_HEIGHT = SM_settings::windowHeight;

//left-most side of the screen
float leftX = -SCREEN_WIDTH / 2;
//right-most side of the screen
float rightX = SCREEN_WIDTH / 2;

//bottom-most side of the screen
float bottomY = -SCREEN_HEIGHT / 2;
//top-most side of the screen
float topY = SCREEN_HEIGHT / 2;

int verticalGridSpaces = SCREEN_HEIGHT / GRID_HEIGHT;
int horizontalGridSpaces = (SCREEN_WIDTH / GRID_WIDTH) + 1;

void DebugDraw::DrawDebugGrid() {

	//vertical lines
	for (int i = 0; i < verticalGridSpaces; i++) {
		AddLine2D({ leftX, bottomY + (GRID_HEIGHT  * (i + 1))  - 23.5f}, {rightX, bottomY + (GRID_HEIGHT * (i + 1)) - 23.5f}, false);
	}
	//horizontal lines
	for (int i = 0; i < horizontalGridSpaces; i++) {
		AddLine2D({leftX + (GRID_WIDTH * (i + 1)), bottomY}, {leftX + (GRID_WIDTH * (i + 1)), topY}, false);
	}
}


