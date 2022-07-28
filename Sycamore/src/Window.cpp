#include "Window.h"

Window::Window() {

    /* Initialize the library */
    if (!glfwInit())
        exit(1);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(480, 360, "Hello world", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glViewport(0, 0, 480, 360);
}

void Window::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        std::cout << "Hello world" << std::endl;
    }
}

Window::~Window() {
	std::cout << "Bye bye" << std::endl;
}