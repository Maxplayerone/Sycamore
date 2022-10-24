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

//used to setup camera
//maybe will change later
static void SetupMatrices(uint shaderID) {
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

//computes the squared magnitude of the line 
//(used mostly in the physics engine)
int DebugDraw::DebugLine2D::LengthSquared() {
	SM_math::vec2 vec = end - start;
	return vec.Lengthquared();
}


//---------------------------------
//		DATA FOR BATCH CONTANTS
//----------------------------------
const uint MAX_DEBUG_OBJECTS = 500;
//(2 * position + 3 * colours) * 2
const unsigned int VERTEX_PER_OBJECT = 10;
float vertices[MAX_DEBUG_OBJECTS * VERTEX_PER_OBJECT];

//should be changed to true if we added an object
//we need to re-setup the buffers
//because we added data to vertices array
bool dirty = false;

uint lineCount = 0;
DebugDraw::DebugLine2D lines2D[MAX_DEBUG_OBJECTS];


//--------------------------------
//			DEBUG
//----------------------------------
static uint numOfCycles = 0;
static void TestVerticesData(float buffer[], uint cyclesBeforeAssertion) {
	uint used_space = (lineCount + 1) * VERTEX_PER_OBJECT;

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

static void PrintLine2D(DebugDraw::DebugLine2D line) {
	std::stringstream ss;

	//new lines don't work
	ss << "Start vector: " << line.start << std::endl;
	ss << "End vector: " << line.end << std::endl;
	ss << "Color: " << line.color << std::endl;

	LOGGER_INFO(ss.str());
}

static void UpdateVerticesLine2D(DebugDraw::DebugLine2D &line2D) {
	float xValue = line2D.start.x;
	float yValue = line2D.start.y;

	for (int i = 0; i < 2; i++) {
		switch (i) {
		case 1:
			xValue = line2D.end.x;
			yValue = line2D.end.y;
			break;
		}

		//that 5 is a number of unique vertex data (aka 2 * position and 3 * color)
		vertices[(i * 5) + (lineCount * VERTEX_PER_OBJECT + 0)] = xValue;
		vertices[(i * 5) + (lineCount * VERTEX_PER_OBJECT + 1)] = yValue;
		vertices[(i * 5) + (lineCount * VERTEX_PER_OBJECT + 2)] = line2D.color.r;
		vertices[(i * 5) + (lineCount * VERTEX_PER_OBJECT + 3)] = line2D.color.g;
		vertices[(i * 5) + (lineCount * VERTEX_PER_OBJECT + 4)] = line2D.color.b;
	}

	lines2D[lineCount] = line2D;

	dirty = true;
	lineCount = lineCount + 1;
}

//---------------------------------------
//		Adding primitives to the batch
//----------------------------------------
void DebugDraw::AddLine2D(SM_math::vec2 start, SM_math::vec2 end, color3 color) {
	DebugLine2D tmpLine;
	tmpLine.start = start;
	tmpLine.end = end;
	tmpLine.color = color;

	UpdateVerticesLine2D(tmpLine);
}


void DebugDraw::AddBox2D(SM_math::vec2 center, float length, color3 color, float _angle) {
	float half = length / 2;

	float top = (center.x + half);
	float bottom = (center.x - half);

	float left = (center.y - half);
	float right = (center.y + half);

	SM_math::vec2 TR = SM_math::Rotate(SM_math::vec2(top, right), _angle, center);
	SM_math::vec2 TL = SM_math::Rotate(SM_math::vec2(top, left), _angle, center);
	SM_math::vec2 BR = SM_math::Rotate(SM_math::vec2(bottom, right), _angle, center);
	SM_math::vec2 BL = SM_math::Rotate(SM_math::vec2(bottom, left), _angle, center);

	AddLine2D(TR, BR, color);
	AddLine2D(TL, BL, color);
	AddLine2D(TL, TR, color);
	AddLine2D(BL, BR, color);
}

#define DRAW_RADIUS_LINES 0

void DebugDraw::AddCircle2D(SM_math::vec2 center, float radius, color3 color) {
#if DRAW_RADIUS_LINES == 0
	const uint radiusCount = 20;
	SM_math::vec2 radiuses[radiusCount];

	//after angleStep angle we have a point (ex. 30, 60, 90, 120...)
	float angleStep = 360 / radiusCount;

	for (int i = 0; i < radiusCount; i++) {
		SM_math::vec2 centerAndRadius = SM_math::vec2(center.x + radius, center.y);
		radiuses[i] = SM_math::Rotate(centerAndRadius, angleStep * i, center);
	}

	for (uint i = 0; i < radiusCount - 1; i++) {
		AddLine2D(radiuses[i], radiuses[i + 1], color);
	}
	//joining the last point with the first one
	AddLine2D(radiuses[radiusCount - 1], radiuses[0], color);

#elif DRAW_RADIUS_LINES == 1
	const uint radiusCount = 20;
	SM_math::vec2 radiuses[radiusCount];

	//after angleStep angle we have a point (ex. 30, 60, 90, 120...)
	float angleStep = 360 / radiusCount;

	for (int i = 0; i < radiusCount; i++) {
		SM_math::vec2 centerAndRadius = SM_math::vec2(center.x + radius, center.y);
		radiuses[i] = SM_math::Rotate(centerAndRadius, angleStep * i, center);
	}

	for (uint i = 0; i < radiusCount; i++) {
		AddLine2D(center, radiuses[i], color);
	}
#endif
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
		AddLine2D({ leftX, bottomY + (SM_settings::GRID_HEIGHT * (i + 1)) - 23.5f }, { rightX, bottomY + (SM_settings::GRID_HEIGHT * (i + 1)) - 23.5f }, { 0.0f, 0.0f, 0.0f });
	}

	//horizontal lines	
	for (int i = 0; i < horizontalGridSpaces; i++) {
		AddLine2D({ leftX + (SM_settings::GRID_WIDTH * (i + 1)), bottomY }, { leftX + (SM_settings::GRID_WIDTH * (i + 1)), topY }, {0.0f, 0.0f, 0.0f});
	}

	usingGrid = true;
}

//--------------------------------
//        overall rendering
//--------------------------------

void DebugDraw::Render() {
	SM_Profiler::MAIN("debug draw render");

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
		//we are changing to clean
		//there is a possibility that we had lines that were DESTROY_ON_FRAME but now we should not draw them 
		//we should clean the array list

		SM_Buffers::BindVertexArray(_vaID);;
		SM_Buffers::BindVertexBuffer(_vbID);
		Shader::UseShader(debugShaderID);
	}

	if (usingGrid) {
		GLCall(glLineWidth(1.0f));
		GLCall(glDrawArrays(GL_LINES, 0, GRID_LINES_COUNT * 2));

		GLCall(glLineWidth(4.0f));
		GLCall(glDrawArrays(GL_LINES, GRID_LINES_COUNT * 2, (lineCount - GRID_LINES_COUNT) * 2));
	}
	else {
		GLCall(glLineWidth(4.0f));
		GLCall(glDrawArrays(GL_LINES, 0, lineCount * 2));
	}

	lineCount = 0;
}