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
#include"Utils/ObjectPool.h"
#include"Utils/Profiler.h"
#include"Utils/Settings.h"
#include"Utils/Serializer.h"

#include"../Math/SM_math.h"

#include"Rendering/Shader.h"
#include"Rendering/DebugDraw.h"

#include"Editor/GameViewport.h"

#include"Buffers/Framebuffer.h"

#include"../Unit tests/Master.h"

uint _fboID = 0;

Window::Window() {
    srand(static_cast <unsigned> (time(0)));

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

    int shaderID = SM_Pool::GetShader();

    SM_math::mat4 modelMat(1.0f);
    SM_math::mat4 viewMat(1.0f);
    SM_math::mat4 projMat(1.0f);
    projMat = SM_math::ortho(orthoProj.left, orthoProj.right, orthoProj.top, orthoProj.bottom, -1.0f, 100.0f);

    Shader::SetUniformMat4f(shaderID, "model", modelMat);
    Shader::SetUniformMat4f(shaderID, "view", viewMat);
    Shader::SetUniformMat4f(shaderID, "projection", projMat);

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

    //checking the unit tests
    //SM_Tests::Init();

    //DebugDraw::DrawDebugGrid();

    _fboID = SM_Pool::GetFramebufferID(SM_settings::windowWidth, SM_settings::windowHeight);

    m_levelEditorScene = new LevelEditorScene();

    //SM_Serializer::Deserialize(m_levelEditorScene);
}

void Window::Run() {
    //default scene
    ImGuiTheme();
    
    while (!glfwWindowShouldClose(m_window)) {
        SM_Profiler::MAIN("Main loop");

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT);       
                
        SM_Buffers::BindFramebuffer(_fboID);

        m_levelEditorScene->OnUpdate(deltaTime.count());         

        SM_Buffers::UnbindFramebuffer();
        
        SM_Profiler::ImGuiRender(); 
        m_levelEditorScene->ImGui();
        SM_Viewport::ImGui();       
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(m_window);

        endTime = std::chrono::high_resolution_clock::now();
        deltaTime = endTime - startTime;
        startTime = endTime;

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(m_window);
        }        
    }
    
}


Window::~Window() {   
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();   

    glfwTerminate();
    SM_Serializer::Serialize();
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

