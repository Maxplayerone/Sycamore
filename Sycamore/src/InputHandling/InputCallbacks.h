#pragma once
#include"KeysHandleler.h"
#include"MouseHandleler.h"

#include"GLFW/glfw3.h"

#include"../smpch.h"

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);

