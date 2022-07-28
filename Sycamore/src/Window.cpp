#include "Window.h"

Window::Window() {

    /* Initialize the library */
    if (!glfwInit())
        exit(1);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(480, 360, "Hello world", NULL, NULL);
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
}

void Window::Run() {
    uint currentBGColor = 0;

    while (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        switch (currentBGColor) {
        case 0:
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            break;
        case 1:
            glClearColor(0.55f, 0.92f, 0.03f, 1.0f);
            break;
        case 2:
            glClearColor(1.0f, 0.16f, 0.85f, 1.0f);
            break;
        }

        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_Q))  currentBGColor = 1;
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_W))  currentBGColor = 2;
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

Window::~Window() {
    glfwTerminate();
}