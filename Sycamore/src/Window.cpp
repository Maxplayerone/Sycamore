#include "Window.h"

Window::Window() {

    /* Initialize the library */
    if (!glfwInit())
        exit(1);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
    if (!m_window)
    {
        LOGGER_ERROR("Cannot initialize glfw!");
        glfwTerminate();
        exit(1);
    }

    //callbacks for the mouse and keyboard input
    glfwSetKeyCallback(m_window, KeyCallBack);
    glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
    glfwSetScrollCallback(m_window, ScrollCallback);
    glfwSetCursorPosCallback(m_window, CursorPosCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glViewport(0, 0, 480, 360);

    if (glewInit() != GLEW_OK)
        LOGGER_ERROR("Cannot initialize glew!");

    LOGGER_INFO("The window has been initialized");

    /*Camera stuff*/
    SetupCamera();
    SetupImGui();
}

void Window::SetupCamera() {
   
    m_ModelMatrix = new ModelMatrix();
    m_ViewMatrix = new ViewMatrix();
    m_ProjMatrix = new ProjectionMatrix();

    Shader* shaderProgram = AssetsPool::Get().GetShader("src/Assets/Shaders/Shader.shader");

    camera = new Camera(*shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_MODEL, m_ModelMatrix->GetModelMatrix(), *shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_VIEW, m_ViewMatrix->GetViewMatrix(), *shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_PROJECTION, m_ProjMatrix->GetProjectionMatrix(), *shaderProgram);
}

void Window::SetupImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::Run() {
    //default scene
    ChangeScene(1);

    while (!glfwWindowShouldClose(m_window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_U)) ChangeScene(1);
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_I)) ChangeScene(0);
        
        if (m_currentScene != nullptr) {
            m_currentScene->OnUpdate(deltaTime.count());
            m_currentScene->ImGui();
        }
        
        ImGui::Begin("window");
        ImGui::SliderFloat("Camera zoom", &cameraScaleValue, 0.0f, 5.0f);
        ImGui::End();
        
        Shader* shaderProgram = AssetsPool::Get().GetShader("src/Assets/Shaders/Shader.shader");
        m_ProjMatrix = new ProjectionMatrix(cameraScaleValue);
        camera->Push(Camera::MatrixType::TYPE_PROJECTION, m_ProjMatrix->GetProjectionMatrix(), *shaderProgram);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
        glfwPollEvents();

        endTime = std::chrono::high_resolution_clock::now();
        deltaTime = endTime - startTime;
        startTime = endTime;
    }
}

void Window::ChangeScene(int sceneIndex) {
    switch (sceneIndex) {
    case 0:
        m_currentScene = new LevelScene();
        break;
    case 1:
        m_currentScene = new LevelEditorScene();
        break;
    default:
        LOGGER_WARNING("Cannot load scene with index %d", sceneIndex);
    }
}

Window::~Window() {
    delete m_ModelMatrix;
    delete m_ProjMatrix;
    delete m_ViewMatrix;
    delete camera;

    delete m_currentScene;

    glfwTerminate();
}

