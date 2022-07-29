#pragma once
#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"
#include"../Buffers/VertexBuffer.h"
#include"../Buffers/VertexBufferLayout.h"

#include"../ECS/GameObject.h"
#include"../ECS/Transform.h"
#include"../ECS/SpriteRenderer.h"

#include"../Utils/AssetsPool.h"
#include"../Utils/ErrorHandling.h"

#define MAX_BATCH_SIZE 1000

class BatchRenderer {
private:
    VertexBufferLayout vertexBufferLayout;
    VertexArray* vertexArray;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    std::vector<GameObject*> objectsForRender;
    float* vertices;

    //the number of indexes in the vertices buffer occupied by a single quad
    const unsigned int VERTICES_DATA_FOR_QUAD = 32;
    //the length of each side of the quad
    const float QUAD_LENGTH = 1.0f;
    //position + color + texCoords + texIndex
    const unsigned int DATA_IN_ONE_VERTEX = 8;

    //prints the context of the vertices array and stops the program
    void TestVertices();

    //used when the vertices buffer is changed
    void SetupBuffers();
    bool rebufferData = true;
    bool oneTimeFlag = true;
public:
    BatchRenderer();
    void Add(GameObject* go);
    void Render();

    bool HasRoom() const { return objectsForRender.size() < MAX_BATCH_SIZE ? true : false; }

    void LoadVerticesData(unsigned int gameObjectIndex);

    //renders a single object (ONLY FOR DEBUG)
    void RenderDebug(GameObject* go);
};

