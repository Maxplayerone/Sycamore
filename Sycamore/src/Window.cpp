#include "Window.h"

//imGui
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"

//input handling
#include"InputHandling/InputCallbacks.h"
#include"InputHandling/KeysHandleler.h"
#include"InputHandling/MouseHandleler.h"

//utilities
#include"Utils/DataTypes.h"
#include"Utils/Logger.h"
#include"Utils/AssetsPool.h"

#include"Settings.h"

Window::Window() {    

    F4 orthoProj{ -((float)SM_settings::windowWidth) / 2,
                            (float)SM_settings::windowWidth / 2 ,
                            -((float)SM_settings::windowHeight) / 2,
                            (float)SM_settings::windowHeight / 2
    };

    /* Window and openGL setup */
    if (!glfwInit())
        exit(1);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(SM_settings::windowWidth, SM_settings::windowHeight, SM_settings::windowName.c_str(), NULL, NULL);
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
    glViewport(0, 0, SM_settings::windowWidth, SM_settings::windowHeight);

    if (glewInit() != GLEW_OK)
        LOGGER_ERROR("Cannot initialize glew!");

    LOGGER_INFO("The window has been initialized");


    /* Camera setup */
    Shader* shaderProgram = AssetsPool::Get().GetShader();

    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::mat4 projMat = glm::mat4(1.0f);
    projMat = glm::ortho(orthoProj.left, orthoProj.right, orthoProj.bottom, orthoProj.top, -1.0f, 100.0f);

    shaderProgram->SetUniformMat4f("model", modelMat);
    shaderProgram->SetUniformMat4f("view", viewMat);
    shaderProgram->SetUniformMat4f("projection", projMat);
   
    //Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    //flags
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //setup style
    ImGui::StyleColorsDark();
    
    //setup platform/renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

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
        
        ImGuiTheme();
        if (m_currentScene != nullptr) {
            m_currentScene->OnUpdate(deltaTime.count());
            m_currentScene->ImGui();
        }
    
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      
        glfwSwapBuffers(m_window);
        glfwPollEvents();

        endTime = std::chrono::high_resolution_clock::now();
        deltaTime = endTime - startTime;
        startTime = endTime;

        /*
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(m_window);
        }
        */
        
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
    /*
    delete m_ModelMatrix;
    delete m_ProjMatrix;
    delete m_ViewMatrix;
    delete camera;
    */
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();   
    delete m_currentScene;

    glfwTerminate();
}

void Window::ImGuiTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();

    //centering the header text
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->SelectableTextAlign = ImVec2(0.5, 0.5);

    style->FramePadding = ImVec2(8, 4);

    //header colors
    style->Colors[ImGuiCol_TitleBg] = ImColor(255, 147, 32, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 147, 32, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

    //disable collapsing
    style->WindowMenuButtonPosition = ImGuiDir_None;
}

