#pragma once

#include"smpch.h"

//openGL
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//utilities
#include"Utils/DataTypes.h"

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
	const uint windowWidth = 960;
	const uint windowHeight = 720;

	F4 orthoProj{ -((float)windowWidth) / 2,
							(float)windowWidth / 2 ,
							-((float)windowHeight) / 2,
							(float)windowHeight / 2
	};

	const std::string windowName = "Sycamore-Engine";

	ModelMatrix* m_ModelMatrix;
	ViewMatrix* m_ViewMatrix;
	ProjectionMatrix* m_ProjMatrix;
	Camera* camera;

	Scene* m_currentScene;

	//for later deletion
	float cameraScaleValue = 3.5f;

	//delta time
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

