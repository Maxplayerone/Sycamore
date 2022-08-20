#include"InputCallbacks.h"

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        KeyHandleler::Get().m_keys[key] = true;
    else if (action == GLFW_RELEASE)
        KeyHandleler::Get().m_keys[key] = false;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        MouseHandleler::Get().mouseButtons[button] = true;
    else if (action == GLFW_RELEASE)
        MouseHandleler::Get().mouseButtons[button] = false;
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    MouseHandleler::Get().SetScrollInput(xoffset, yoffset);
}

void CursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    MouseHandleler::Get().SetMousePosAbsolute(xPos, yPos);
}
