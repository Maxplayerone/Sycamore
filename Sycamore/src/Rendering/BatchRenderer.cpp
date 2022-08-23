#include"BatchRenderer.h"

#include"../ECS/Transform.h"
#include"../ECS/SpriteRenderer.h"

#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"
#include"../Utils/Profiler.h"
#include"../Utils/ObjectPool.h"

#include"../Rendering/Shader.h"

#include"../Buffers/VertexBuffer.h"
#include"../Buffers/IndexBuffer.h"
#include"../Buffers/VertexArray.h"

uint vaID;
uint vbID;
uint ibID;
uint BatchShaderID;

VertexBufferLayout vertexBufferLayout;

bool reloadBuffers = false;

BatchRenderer::BatchRenderer() {
    vertices = new float[MAX_BATCH_SIZE * VERTICES_DATA_FOR_QUAD]; //1000 * 32 * 32bytes per float = 64000 bytes

    vertexBufferLayout.AddFloat(2); //position vertex
    vertexBufferLayout.AddFloat(3); //color vertex
    vertexBufferLayout.AddFloat(2); //texture vertex
    vertexBufferLayout.AddFloat(1); //texture index
}

void BatchRenderer::Add(GameObject& go) {
    //auto itr = std::find(objectsForRender.begin(), objectsForRender.end(), go);
    //the object is already in the vector
    //if (itr != objectsForRender.end()) return;

    objectsForRender[gameObjectCount++] = go;
}

void BatchRenderer::Render() {
    SM_Profiler::MAIN("Batch render");
    //dirty flagging
    for (int i = 0; i < gameObjectCount; i++) {
        //if the position/color/texture of any object changed
        if (objectsForRender[i].GetComponent<Transform>()->IsDirty() || objectsForRender[i].GetComponent<SpriteRenderer>()->IsDirty() || oneTimeFlag) {
            //LOGGER_INFO("Re-setupping the batch renderer");
            LoadVerticesData(i);
            objectsForRender[i].GetComponent<Transform>()->Clean();
            objectsForRender[i].GetComponent<SpriteRenderer>()->Clean();

            reloadBuffers = true;
        }
    }
    oneTimeFlag = false;
    //TestVertices(2);

    if (reloadBuffers) {
        vbID = SM_Buffers::CreateVertexBuffer(gameObjectCount * VERTICES_DATA_FOR_QUAD * sizeof(float), vertices);
        vaID = SM_Buffers::CreateVertexArray();
        SM_Buffers::AddVertexBuffer(vaID, vbID, vertexBufferLayout);
        ibID = SM_Buffers::CreateIndexBuffer(6 * gameObjectCount);
        BatchShaderID = SM_Pool::GetShaderID();

        reloadBuffers = false;
    }
    else {
        SM_Buffers::BindVertexArray(vaID);;
        SM_Buffers::BindIndexBuffer(ibID);
        SM_Buffers::BindVertexBuffer(vbID);
        Shader::UseShader(BatchShaderID);
    }


    GLCall(glDrawElements(GL_TRIANGLES, 6 * gameObjectCount, GL_UNSIGNED_INT, nullptr));
}

void BatchRenderer::LoadVerticesData(unsigned int gameObjectIndex) {
    GameObject go = objectsForRender[gameObjectIndex];
    Transform* trans = go.GetComponent<Transform>();
    SpriteRenderer* rend = go.GetComponent<SpriteRenderer>();

    unsigned int texCoordsIndex = 0;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    unsigned int gameObjectOffset = gameObjectIndex * VERTICES_DATA_FOR_QUAD;

    //every iteration of the loop creates a single "point" of a quad
    for (int i = 0; i < 4; i++) {
        switch (i) {
        case 1:
            offsetX = trans->GetScale().x;
            break;
        case 2:
            offsetX = 0.0f;
            offsetY = trans->GetScale().y;
            break;
        case 3:
            offsetX = trans->GetScale().x;
            break;
        default:
            break;
        }

        vertices[(0 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->GetPos().x + offsetX;
        vertices[(1 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->GetPos().y + offsetY;
        vertices[(2 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetColor4().r;
        vertices[(3 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetColor4().g;
        vertices[(4 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetColor4().b;
        vertices[(5 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        vertices[(6 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        vertices[(7 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexIndex();
    }
}

static uint cycles = 0;
void BatchRenderer::TestVertices(uint cyclesCount) {
    LOGGER_INFO("Vertices buffer");
    for (int i = 0; i < 2 * VERTICES_DATA_FOR_QUAD; i++) {
        if (i % DATA_IN_ONE_VERTEX == 0) LOGGER_WARNING("New vertex");
        if (i % VERTICES_DATA_FOR_QUAD == 0) LOGGER_ERROR("New game object");
        std::stringstream ss;
        ss << "Element at index " << i << " | " << vertices[i];
        LOGGER_INFO(ss.str());
    }
    std::cout << std::endl << std::endl << std::endl;
    cycles++;
    if (cycles >= cyclesCount)
        ASSERT(false);
}