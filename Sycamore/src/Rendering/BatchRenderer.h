#pragma once

#include"../ECS/GameObject.h"

#include"../Buffers/VertexBufferLayout.h"

#include"../smpch.h"
#include"../Utils/DataTypes.h"

#define MAX_BATCH_SIZE 1000

class BatchRenderer {
private:
    GameObject* objectsForRender[MAX_BATCH_SIZE];
    uint gameObjectCount = 0;
    float* vertices;

    //the number of indexes in the vertices buffer occupied by a single quad
    const unsigned int VERTICES_DATA_FOR_QUAD = 32;
    //position + color + texCoords + texIndex
    const unsigned int DATA_IN_ONE_VERTEX = 8;

    //prints the context of the vertices array and stops the program
    //cyclesCount - how many times the function will run before assertion
    void TestVertices(uint cyclesCount);

    bool oneTimeFlag = true; //ignore this please
public:
    BatchRenderer();
    void Add(GameObject* go);
    void Delete(GameObject* go);
    void Render();

    bool HasRoom() const { return (gameObjectCount < MAX_BATCH_SIZE) ? true : false; }

    void LoadVerticesData(unsigned int gameObjectIndex);
};

