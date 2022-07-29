#pragma once
#include<iostream>

//openGL
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//utilities
#include"Utils/DataTypes.h"
#include"Utils/Logger.h"
#include"Utils/AssetsPool.h"

//input handling
#include"InputHandling/InputCallbacks.h"
#include"InputHandling/KeysHandleler.h"
#include"InputHandling/MouseHandleler.h"

//scene managment
#include"SceneManagment/LevelEditorScene.h"
#include"SceneManagment/LevelScene.h"

//camera
#include"Camera/Camera.h"
#include"Camera/ModelMatrix.h"
#include"Camera/ProjectionMatrix.h"
#include"Camera/ViewMatrix.h"

//imGui
#include"../vendor/imGui/imgui.h"
#include"../vendor/imGui/imgui_impl_glfw.h"
#include"../vendor/imGui/imgui_impl_opengl3.h"

class Window
{
private:
	GLFWwindow* m_window;

	const uint windowWidth = 960;
	const uint windowHeight = 720;
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

	void SetupCamera();
	void SetupImGui();

	void ChangeScene(int sceneIndex);
public:
	Window();
	~Window();

	void Run();
};

