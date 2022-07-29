#include"BatchRenderer.h"

void BatchRenderer::Add(GameObject* go) {
    auto itr = std::find(objectsForRender.begin(), objectsForRender.end(), go);
    //the object is already in the vector
    if (itr != objectsForRender.end()) return;

    objectsForRender.push_back(go);
}

void BatchRenderer::Render() {

    for (int i = 0; i < objectsForRender.size(); i++) {
        //if the position/color/texture of any object changed
        if (objectsForRender[i]->GetComponent<Transform>()->IsDirty() || objectsForRender[i]->GetComponent<SpriteRenderer>()->IsDirty() || oneTimeFlag) {
            LoadVerticesData(i);
            //std::cout << "Need to rebuffer data :/" << std::endl;
            rebufferData = true;
        }
    }
    //this is one of the stupidest things I did as a programmer, but it works
    oneTimeFlag = false;
    //TestVertices();
    if (rebufferData) {
        SetupBuffers();
        rebufferData = false;
    }

    Shader* shader = AssetsPool::Get().GetShader("src/Assets/Shaders/Shader.shader");
    shader->UseProgram();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

BatchRenderer::BatchRenderer() {
    vertices = new float[MAX_BATCH_SIZE * VERTICES_DATA_FOR_QUAD]; //1000 * 32 * 32bytes per float = 64000 bytes

    vertexArray = new VertexArray();

    //every...
    vertexBufferLayout.AddFloat(2); //position vertex
    vertexBufferLayout.AddFloat(3); //color vertex
    vertexBufferLayout.AddFloat(2); //texture vertex
    vertexBufferLayout.AddFloat(1); //texture index
    //8 * 4 positions in the vertices buffer a new quad appears
    //(you multiply by 4 because the quad
    //needs at least four points to render it
    //aka. bottom-left, top-left etc.)


    SetupBuffers();
}

void BatchRenderer::LoadVerticesData(unsigned int gameObjectIndex) {
    GameObject* go = objectsForRender[gameObjectIndex];
    Transform* trans = go->GetComponent<Transform>();
    SpriteRenderer* rend = go->GetComponent<SpriteRenderer>();

    unsigned int texCoordsIndex = 0;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    unsigned int gameObjectOffset = gameObjectIndex * VERTICES_DATA_FOR_QUAD;

    //every iteration of the loop creates a single "point" of a quad
    for (int i = 0; i < 4; i++) {
        switch (i) {
        case 1:
            offsetX = QUAD_LENGTH;
            break;
        case 2:
            offsetX = 0.0f;
            offsetY = QUAD_LENGTH;
            break;
        case 3:
            offsetX = QUAD_LENGTH;
            break;
        default:
            break;
        }

        vertices[(0 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->GetPos(0) + offsetX;
        vertices[(1 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->GetPos(1) + offsetY;
        vertices[(2 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetR();
        vertices[(3 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetG();
        vertices[(4 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetB();
        vertices[(5 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        vertices[(6 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        vertices[(7 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexIndex();
    }
}

void BatchRenderer::TestVertices() {
    std::cout << "Vertices array" << std::endl;
    for (int i = 0; i < 2 * VERTICES_DATA_FOR_QUAD; i++) {
        if (i % DATA_IN_ONE_VERTEX == 0) std::cout << "new vertex " << std::endl;
        if (i % VERTICES_DATA_FOR_QUAD == 0) std::cout << "new game object" << std::endl;

        std::cout << "Element at index " << i << " | " << vertices[i] << std::endl;
    }
    ASSERT(false);
}

void BatchRenderer::SetupBuffers() {
    vertexBuffer = new VertexBuffer(objectsForRender.size() * VERTICES_DATA_FOR_QUAD * sizeof(float), vertices);
    vertexArray->AddVertexBuffer(*vertexBuffer, vertexBufferLayout);
    indexBuffer = new IndexBuffer(6 * objectsForRender.size());
}

void BatchRenderer::RenderDebug(GameObject* go) {
    float* _vertices = new float[VERTICES_DATA_FOR_QUAD];
    Transform* trans = go->GetComponent<Transform>();
    SpriteRenderer* rend = go->GetComponent<SpriteRenderer>();

    unsigned int texCoordsIndex = 0;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    unsigned int gameObjectOffset = 0;

    //every iteration of the loop creates a single "point" of a quad
    for (int i = 0; i < 4; i++) {
        switch (i) {
        case 1:
            offsetX = QUAD_LENGTH;
            break;
        case 2:
            offsetX = 0.0f;
            offsetY = QUAD_LENGTH;
            break;
        case 3:
            offsetX = QUAD_LENGTH;
            break;
        default:
            break;
        }

        _vertices[(0 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->GetPos(0) + offsetX;
        _vertices[(1 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = trans->GetPos(1) + offsetY;
        _vertices[(2 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetR();
        _vertices[(3 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetG();
        _vertices[(4 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetB();
        _vertices[(5 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        _vertices[(6 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexCoords()[texCoordsIndex++];
        _vertices[(7 + (DATA_IN_ONE_VERTEX * i)) + gameObjectOffset] = rend->GetTexIndex();
    }

    LOGGER_INFO("Vertices buffer");
    for (int i = 0; i < VERTICES_DATA_FOR_QUAD; i++) {
        if (i % DATA_IN_ONE_VERTEX == 0) LOGGER_INFO("New vertex");
        if (i % VERTICES_DATA_FOR_QUAD == 0) LOGGER_INFO("New gameobject");

        std::cout << "Element at index " << i << " | " << _vertices[i] << std::endl;
    }

    vertexBuffer = new VertexBuffer(VERTICES_DATA_FOR_QUAD * sizeof(float), _vertices);
    vertexArray->AddVertexBuffer(*vertexBuffer, vertexBufferLayout);
    indexBuffer = new IndexBuffer(6);
    
    Shader* shader = AssetsPool::Get().GetShader("src/Assets/Shaders/Shader.shader");
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
