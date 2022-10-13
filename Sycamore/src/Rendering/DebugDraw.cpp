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
#include"../Utils/Profiler.h"

#include"../Rendering/Shader.h"

uint debugShaderID;
uint _vbID;
uint _vaID;

//for later deletion
void SetupMatrices(uint shaderID) {
	F4 orthoProj{ -((float)SM_settings::windowWidth) / 2,
				   (float)SM_settings::windowWidth / 2 ,
				   -((float)SM_settings::windowHeight) / 2,
				   (float)SM_settings::windowHeight / 2
	};

	SM_math::mat4 modelMat(1.0f);
	SM_math::mat4 viewMat(1.0f);
	SM_math::mat4 projMat(1.0f);
	projMat = SM_math::ortho(orthoProj.left, orthoProj.right, orthoProj.top, orthoProj.bottom, -1.0f, 100.0f);

	Shader::SetUniformMat4f(debugShaderID, "model", modelMat);
	Shader::SetUniformMat4f(debugShaderID, "view", viewMat);
	Shader::SetUniformMat4f(debugShaderID, "projection", projMat);
}

int DebugDraw::DebugLine2D::LengthSquared() {
	SM_math::vec2 vec = end - start;
	return vec.Lengthquared();
}


const uint MAX_DEBUG_OBJECTS = 500;
//(2 * position + 3 * colours) * 2
const unsigned int VERTEX_PER_OBJECT = 10;
float vertices[MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT];

//should be changed to true if we added an object
//we need to re-setup the buffers
//because we added data to vertices array
bool dirty = false;

uint debugLine2DCount = 0;
DebugDraw::DebugLine2D lines2D[MAX_DEBUG_OBJECTS];

static uint numOfCycles = 0;
void TestVerticesData(float buffer[], uint cyclesBeforeAssertion) {
	uint used_space = (debugLine2DCount + 1) * VERTEX_PER_OBJECT;

	if (numOfCycles == (cyclesBeforeAssertion - 1)) {
		for (int i = 0; i < used_space; i++) {
			if (i % VERTEX_PER_OBJECT == 0) {
				std::stringstream ss;
				ss << "Line number " << i / 10;
				LOGGER_INFO(ss.str());
			}

			std::stringstream ss;
			ss << "Line at index " << i << ": " << buffer[i];
			LOGGER_ERROR(ss.str());
		}
	}

	numOfCycles++;
	if(numOfCycles >= cyclesBeforeAssertion)
		ASSERT(false);
}


//---------------------------
//		lines2D
//---------------------------

void DeleteFromVertices(uint arrayIndex) {

	
	for (uint i = 0; i < VERTEX_PER_OBJECT; i++) {
		vertices[i + (arrayIndex * VERTEX_PER_OBJECT)] = 0.0f;
	}
	lines2D[arrayIndex].isDead = true;
	lines2D[arrayIndex].lifetimeFlag = DebugDraw::HAS_LIFETIME;
	dirty = true;
}

void PrintLine2D(DebugDraw::DebugLine2D line) {
	std::stringstream ss;

	//new lines don't work
	ss << "Start vector: " << line.start << std::endl;
	ss << "End vector: " << line.end << std::endl;
	ss << "Color: " << line.color << std::endl;
	ss << "Lifetime: " << line.lifetime << std::endl;

	LOGGER_INFO(ss.str());
}

int UpdateVerticesLine2D(DebugDraw::DebugLine2D &line2D) {
	float xValue = line2D.start.x;
	float yValue = line2D.start.y;

	//index of the first place in the lines2D
	//array in which there is no line
	//(the line might be dead)
	int freeBufferSpaceIndex = -1;

	for (int i = 0; i < MAX_DEBUG_OBJECTS; i++) {
		if (lines2D[i].isDead == true) {
			freeBufferSpaceIndex = i;
			break;
		}
	}

	if (freeBufferSpaceIndex == -1) {
		LOGGER_ERROR("batch for debug drawing overflow!");
		ASSERT(false);
	}

	for (int i = 0; i < 2; i++) {
		switch (i) {
		case 1:
			xValue = line2D.end.x;
			yValue = line2D.end.y;
			break;
		}

		//that 5 is a number of unique vertex data (aka 2 * position and 3 * color)
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 0)] = xValue;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 1)] = yValue;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 2)] = line2D.color.r;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 3)] = line2D.color.g;
		vertices[(i * 5) + (freeBufferSpaceIndex * VERTEX_PER_OBJECT + 4)] = line2D.color.b;
	}

	lines2D[freeBufferSpaceIndex] = line2D;
	lines2D[freeBufferSpaceIndex].isDead = false;

	//std::stringstream ss;
	//ss << "Line at index " << freeBufferSpaceIndex << " is " << lines2D[freeBufferSpaceIndex].isDead;
	//LOGGER_INFO(ss.str());

	debugLine2DCount++;
	dirty = true;

	return freeBufferSpaceIndex;
}

//methods with lifetime
void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, float lifetime) {
	DebugLine2D tmpLine;
	tmpLine.start = start;
	tmpLine.end = end;
	tmpLine.color = color;

	tmpLine.lifetimeFlag = IGNORE_LIFETIME;
	tmpLine.lifetime = lifetime;

	UpdateVerticesLine2D(tmpLine);
}
void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, float lifetime) {
	DebugDraw::AddLine2D(start, end, {1.0f, 1.0f, 1.0f}, lifetime);
}

//methods without lifetime
int DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color, flag _flag) {
	DebugLine2D tmpLine;
	tmpLine.start = start;
	tmpLine.end = end;
	tmpLine.color = color;

	tmpLine.lifetimeFlag = _flag;
	tmpLine.lifetime = 0.0f;

	int index = UpdateVerticesLine2D(tmpLine);

	return index;
}
int DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, flag _flag) {
	return AddLine2D(start, end, { 0.0f, 0.0f, 0.0f }, _flag);
}

void DebugDraw::SetLine2DIgnoreLifetime(int index, flag _lifetimeFlag) {
	lines2D[index].lifetimeFlag = _lifetimeFlag;
}

//-------------------------------------
//			GRID
//---------------------------------------

const int SCREEN_WIDTH = SM_settings::windowWidth;
const int SCREEN_HEIGHT = SM_settings::windowHeight;

float leftX = -SCREEN_WIDTH / 2;
float rightX = SCREEN_WIDTH / 2;
float bottomY = -SCREEN_HEIGHT / 2;
float topY = SCREEN_HEIGHT / 2;

const int verticalGridSpaces = SCREEN_HEIGHT / SM_settings::GRID_HEIGHT;
//if we have a higher value we get a access violation error
const int horizontalGridSpaces = (SCREEN_WIDTH / SM_settings::GRID_WIDTH);

const int GRID_LINES_COUNT = 51;

//if we use a DrawDebugGrid method
//we change it to true
//and we have two batches in the render function
bool usingGrid = false;

void DebugDraw::DrawDebugGrid() {
	//vertical lines

	for (int i = 0; i < verticalGridSpaces; i++) {
		AddLine2D({ leftX, bottomY + (SM_settings::GRID_HEIGHT * (i + 1)) - 23.5f }, { rightX, bottomY + (SM_settings::GRID_HEIGHT * (i + 1)) - 23.5f });
	}

	//horizontal lines	
	for (int i = 0; i < horizontalGridSpaces; i++) {
		AddLine2D({ leftX + (SM_settings::GRID_WIDTH * (i + 1)), bottomY }, { leftX + (SM_settings::GRID_WIDTH * (i + 1)), topY });
	}

	usingGrid = true;
}

//--------------------------------
//        overall rendering
//--------------------------------

void CheckForDeadLines() {
	SM_Profiler::SUB("debug draw update frame");

	for (uint i = 0; i < debugLine2DCount; i++) {
		if (lines2D[i].lifetimeFlag == DebugDraw::DESTROY_ON_FRAME) {
			DeleteFromVertices(i);
		}
		else if(lines2D[i].lifetimeFlag == DebugDraw::IGNORE_LIFETIME) {
			lines2D[i].lifetime--;

			if ((lines2D[i].lifetime <= 0.0f)) {
				DeleteFromVertices(i);
			}
		}
	}
}


void DebugDraw::Render() {
	SM_Profiler::MAIN("debug draw render");

	CheckForDeadLines();

	if(dirty) {
		_vaID = SM_Buffers::CreateVertexArray();

		VertexBufferLayout vbLayout;
		vbLayout.AddFloat(2); // position
		vbLayout.AddFloat(3); // colour

		debugShaderID = SM_Pool::GetShader("debugDrawing.shader");

		_vbID = SM_Buffers::CreateVertexBuffer(MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT * sizeof(float), vertices);
		SM_Buffers::AddVertexBuffer(_vaID, _vbID, vbLayout);
		SetupMatrices(debugShaderID);
		Shader::UseShader(debugShaderID);

		dirty = false;
	}
	else {
		SM_Buffers::BindVertexArray(_vaID);;
		SM_Buffers::BindVertexBuffer(_vbID);
		Shader::UseShader(debugShaderID);
	}

	if (usingGrid) {
		GLCall(glLineWidth(1.0f));
		GLCall(glDrawArrays(GL_LINES, 0, GRID_LINES_COUNT * 2));

		GLCall(glLineWidth(4.0f));
		GLCall(glDrawArrays(GL_LINES, GRID_LINES_COUNT * 2, (debugLine2DCount - GRID_LINES_COUNT) * 2));
	}
	else {
		GLCall(glLineWidth(4.0f));
		GLCall(glDrawArrays(GL_LINES, 0, debugLine2DCount * 2));
	}
}


//--------------------------------
//			boxes 2D
//---------------------------------
void DebugDraw::AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions, color3 color, float lifetime) {
	float halfX = dimensions.x / 2;
	float halfY = dimensions.y / 2;

	float top = center.x + halfX;
	float bottom = center.x - halfX;

	float left = center.y - halfY;
	float right = center.y + halfY;

	AddLine2D({ top, right }, { bottom, right }, color, lifetime);
	AddLine2D({ top, left }, { bottom, left }, color, lifetime);
	AddLine2D({ top, left }, { top, right }, color, lifetime);
	AddLine2D({ bottom, left }, { bottom, right }, color, lifetime);
}



int DebugDraw::AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions, color3 color) {
	float halfX = dimensions.x / 2;
	float halfY = dimensions.y / 2;

	float top = center.x + halfX;
	float bottom = center.x - halfX;

	float left = center.y - halfY;
	float right = center.y + halfY;

	int firstLineIndex = AddLine2D({ top, right }, { bottom, right }, color);
	int second = AddLine2D({ top, left }, { bottom, left }, color);
	int third = AddLine2D({ top, left }, { top, right }, color);
	int fourth = AddLine2D({ bottom, left }, { bottom, right }, color);

	/*
	std::stringstream ss;
	ss << "First " << firstLineIndex << " second " << second << " third " << third << " fourth " << fourth;
	LOGGER_WARNING(ss.str());
	*/
	return firstLineIndex;
}

int DebugDraw::AddBox2D(SM_math::vec2 center, SM_math::vec2 dimensions) {
	return AddBox2D(center, dimensions, { 0.0f, 0.0f, 0.0f });
}

int DebugDraw::AddBox2D(SM_math::vec2 center, float length, color3 color) {
	return AddBox2D(center, { length, length }, color);
}

int DebugDraw::AddBox2D(SM_math::vec2 center, float length) {
	return AddBox2D(center, {length, length}, {0.0f, 0.0f, 0.0f});
}

void DebugDraw::AddBox2D(SM_math::vec2 center, float length, float angle, float lifetime) {
	float half = length / 2;

	SM_math::mat4 matrix(1.0f);
	matrix = SM_math::MatrixRotation(matrix, angle);

	float top = (center.x + half);
	float bottom = (center.x - half);

	float left = (center.y - half);
	float right = (center.y + half);

	SM_math::vec2 TR = matrix * SM_math::vec2(top, right);
	SM_math::vec2 TL = matrix * SM_math::vec2(top, left);
	SM_math::vec2 BR = matrix * SM_math::vec2(bottom, right);
	SM_math::vec2 BL = matrix * SM_math::vec2(bottom, left);

	AddLine2D(TR, BR, { 0.54f, 0.95f, 0.36f }, lifetime);
	AddLine2D(TL, BL, { 0.54f, 0.95f, 0.36f }, lifetime);
	AddLine2D(TL, TR, { 0.54f, 0.95f, 0.36f }, lifetime);
	AddLine2D(BL, BR, { 0.54f, 0.95f, 0.36f }, lifetime);
}

int DebugDraw::AddBox2D(SM_math::vec2 center, float length, float angle) {
	float half = length / 2;

	SM_math::mat4 matrix(1.0f);
	matrix = SM_math::MatrixRotation(matrix, angle);

	float top = (center.x + half);
	float bottom = (center.x - half);

	float left = (center.y - half);
	float right = (center.y + half);

	SM_math::vec2 TR = matrix * SM_math::vec2(top, right);
	SM_math::vec2 TL = matrix * SM_math::vec2(top, left);
	SM_math::vec2 BR = matrix * SM_math::vec2(bottom, right);
	SM_math::vec2 BL = matrix * SM_math::vec2(bottom, left);

	int firstIndex = AddLine2D(TR, BR, { 0.54f, 0.95f, 0.36f});
	AddLine2D(TL, BL, { 0.54f, 0.95f, 0.36f });
	AddLine2D(TL, TR, { 0.54f, 0.95f, 0.36f });
	AddLine2D(BL, BR, { 0.54f, 0.95f, 0.36f });

	return firstIndex;
}


//---------------------------------
//			Circles 2D
//---------------------------------

void DebugDraw::AddCircle2D(SM_math::vec2 center, float radius, color3 color) {
	const uint radiusCount = 20;
	SM_math::vec2 radiuses[radiusCount];

	SM_math::mat4 rotation(1.0f);
	float angleStep = 360 / radiusCount;
	
	for (int i = 0; i < radiusCount; i++) {

		rotation = SM_math::MatrixRotation(rotation, angleStep * i);

		radiuses[i] = rotation * SM_math::vec2(center.x + radius, 0);
	}
	
	for (uint i = 0; i < radiusCount - 1; i++) {
		AddLine2D(radiuses[i], radiuses[i + 1], color);
	}
	//joining the last point with the first one
	AddLine2D(radiuses[radiusCount - 1], radiuses[0], color);
}