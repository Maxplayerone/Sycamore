#include"DebugDraw.h"

#include"../smpch.h"
#include"../Utils/Settings.h"

#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"
#include"../Buffers/VertexBuffer.h"
#include"../Buffers/VertexBufferLayout.h"

#include"../Utils/ObjectPool.h"
#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"
#include"../Utils/DataTypes.h"

#include"../Rendering/Shader.h"

const uint MAX_DEBUG_OBJECTS = 50;
//(2 * position + 3 * colours) * 2
const unsigned int VERTEX_PER_OBJECT = 10;
float vertices[MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT];

//should be changed to true if we added an object
//we need to re-setup the buffers
//because we added data to vertices array
bool dirty = false;

uint _vbID;
uint _vaID;
uint debugDrawShaderID;

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


void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime) {
	DebugLine2D tmpLine;
	tmpLine.start = start;
	tmpLine.end = end;
	tmpLine.color = color;
	tmpLine.hasLifetime = true;
	tmpLine.lifetime = lifetime;
	tmpLine.isFree = true;
	lines2D[debugLine2DCount] = tmpLine;

	UpdateVerticesLine2D();
}
void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime) {
	DebugDraw::AddLine2D(start, end, {1.0f, 1.0f, 1.0f}, lifetime);
}
void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, bool hasLifetime) {
	DebugLine2D tmpLine;
	tmpLine.start = start;
	tmpLine.end = end;
	tmpLine.color = { 1.0f, 1.0f, 1.0f };
	tmpLine.hasLifetime = hasLifetime;
	tmpLine.lifetime = 1.0f;
	tmpLine.isFree = true;
	lines2D[debugLine2DCount] = tmpLine;

	UpdateVerticesLine2D();
}
void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end) {
	DebugDraw::AddLine2D(start, end, { 0.0f, 0.0f, 0.0f }, 1.0f);
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
	if(dirty) {
		_vaID = SM_Buffers::CreateVertexArray();

		VertexBufferLayout vbLayout;
		vbLayout.AddFloat(2); // position
		vbLayout.AddFloat(3); // colour

		_vbID = SM_Buffers::CreateVertexBuffer(MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT * sizeof(float), vertices);
		SM_Buffers::AddVertexBuffer(_vaID, _vbID, vbLayout);

		GLCall(glLineWidth(1.0f));

		debugDrawShaderID = SM_Pool::GetShaderID();
		Shader::UseShader(debugDrawShaderID);

		dirty = false;
	}
	else {
		SM_Buffers::BindVertexArray(_vaID);;
		SM_Buffers::BindVertexBuffer(_vbID);
		Shader::UseShader(debugDrawShaderID);
	}
	
	GLCall(glDrawArrays(GL_LINES, 0, 2 * debugLine2DCount));
}

const int SCREEN_WIDTH = SM_settings::windowWidth;
const int SCREEN_HEIGHT = SM_settings::windowHeight;

float leftX = -SCREEN_WIDTH / 2;
float rightX = SCREEN_WIDTH / 2;
float bottomY = -SCREEN_HEIGHT / 2;
float topY = SCREEN_HEIGHT / 2;

int verticalGridSpaces = SCREEN_HEIGHT / SM_settings::GRID_HEIGHT;
//if we have a higher value we get a access violation error
int horizontalGridSpaces = (SCREEN_WIDTH / SM_settings::GRID_WIDTH) - 4;

void DebugDraw::DrawDebugGrid() {
	//vertical lines
	for (int i = 0; i < verticalGridSpaces; i++) {
		AddLine2D({ leftX, bottomY + (SM_settings::GRID_HEIGHT * (i + 1)) - 23.5f }, { rightX, bottomY + (SM_settings::GRID_HEIGHT * (i + 1)) - 23.5f }, false);
	}
	
	//horizontal lines

	
	for (int i = 0; i < horizontalGridSpaces; i++) {
		AddLine2D( {leftX + (SM_settings::GRID_WIDTH * (i + 1)), bottomY} ,  {leftX + (SM_settings::GRID_WIDTH * (i + 1)), topY} , false);
	}
	
}


