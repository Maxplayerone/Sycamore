#pragma once

#include"../ECS/GameObject.h"

#include"../Buffers/VertexBufferLayout.h"
#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"
#include"../Buffers/VertexBuffer.h"

#include"../smpch.h"
#include"../Utils/DataTypes.h"

#define MAX_BATCH_SIZE 1000

class BatchRenderer {
private:
    VertexBufferLayout vertexBufferLayout;
    VertexArray vertexArray;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    GameObject objectsForRender[MAX_BATCH_SIZE];
    uint gameObjectCount = 0;
    float* vertices;

    //the number of indexes in the vertices buffer occupied by a single quad
    const unsigned int VERTICES_DATA_FOR_QUAD = 32;
    //position + color + texCoords + texIndex
    const unsigned int DATA_IN_ONE_VERTEX = 8;

    //prints the context of the vertices array and stops the program
    //cyclesCount - how many times the function will run before assertion
    void TestVertices(uint cyclesCount); 

    //used when the vertices buffer is changed
    void SetupBuffers();

    bool oneTimeFlag = true; //ignore this please
public:
    BatchRenderer();
    void Add(GameObject& go);
    void Render();

    bool HasRoom() const { return (gameObjectCount < MAX_BATCH_SIZE) ? true : false; }

    void LoadVerticesData(unsigned int gameObjectIndex);

    //renders a single object (ONLY FOR DEBUG)
    void RenderDebug(GameObject& go);
};

