#pragma once

#include"smpch.h"

//openGL
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//scene managment
#include"SceneManagment/LevelEditorScene.h"
#include"SceneManagment/LevelScene.h"

//camera
#include"Camera/Camera.h"
#include"Camera/ModelMatrix.h"
#include"Camera/ProjectionMatrix.h"
#include"Camera/ViewMatrix.h"

class Window
{
private:
	GLFWwindow* m_window;

	ModelMatrix* m_ModelMatrix = nullptr;
	ViewMatrix* m_ViewMatrix = nullptr;
	ProjectionMatrix* m_ProjMatrix = nullptr;
	Camera* camera = nullptr;

	Scene* m_currentScene = nullptr;

	//delta time
	//maybe should use floats instead of this thingy?
	std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point endTime;
	std::chrono::duration<float> deltaTime;

	void ChangeScene(int sceneIndex);
public:
	Window();
	~Window();

	void Run();

	//sets the imGui style
	void ImGuiTheme();
};
