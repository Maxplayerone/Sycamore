#pragma once
#include<iostream>

#include"GLFW/glfw3.h"

#include"Utils/DataTypes.h"

class Window
{
private:
	GLFWwindow* m_window;
public:
	Window();
	~Window();

	void Run();
};

