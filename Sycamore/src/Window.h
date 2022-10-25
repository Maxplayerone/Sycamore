#pragma once

#include"smpch.h"

//openGL
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//scene managment
#include"SceneManagment/LevelEditorScene.h"
#include"SceneManagment/LevelScene.h"

class Window
{
private:
	GLFWwindow* m_window;

	LevelEditorScene* m_levelEditorScene;

	//delta time
	//maybe should use floats instead of this thingy?
	std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point endTime;
	std::chrono::duration<float> deltaTime;

	//saving/loading imgui window
	bool isEnabledSave = true;
	bool isEnabledLoad = true;

	int runtimeResult = -1;
	//value returned from the runtime start/stop buttons
	//0 - start
	//1 - stop
	bool cleanUp = false;
	//used to cleanUp scenes while transitioning between runtime and stuff`

	//destroys the last existing scene (used along side the load button)
	void CleanUp();
public:
	Window();
	~Window();

	void Run();

	//sets the imGui style
	void ImGuiTheme();
	void MainImgui();
};
