#pragma once
#include<iostream>

//openGL
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//utilities
#include"Utils/DataTypes.h"
#include"Utils/Logger.h"

//input handling
#include"InputHandling/InputCallbacks.h"
#include"InputHandling/KeysHandleler.h"
#include"InputHandling/MouseHandleler.h"

class Window
{
private:
	GLFWwindow* m_window;
public:
	Window();
	~Window();

	void Run();
};

