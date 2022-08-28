#pragma once

#include"../../Math/SM_math.h"

typedef unsigned int uint;

class MouseHandleler {
private:
	MouseHandleler();

	void SetMousePosModel();

	SM_math::vec2 viewportSize;
	SM_math::vec2 viewportPos;
public:

	~MouseHandleler() { delete[] mouseButtons; }

	//deletes an exisitng copy of the class if there is one
	MouseHandleler(const MouseHandleler&) = delete;

	static MouseHandleler& Get() {
		static MouseHandleler instance;
		return instance;
	}

	bool* mouseButtons = new bool[3];
	SM_math::vec2 offset;
	//will change for my vector but I need
	//glm's one for matrix multiplication
	SM_math::vec2 position;
	SM_math::vec2 posModel;
	SM_math::vec2 viewportAbsPos;

	int ArrayLength() { return 3; }

	bool IsMouseButtonPressed(int button);

	void SetScrollInput(double x, double y);
	SM_math::vec2 GetScrollInput() const { return offset; }
	bool IsScrolling();

	//gets x and y position of the mouse in relation to the screen
	void SetMousePosAbsolute(double x, double y);

	SM_math::vec2 GetMousePosAbs() const { return position; }
	//returns the position of the mouse in model space 
	//(used for block placing in the editor)
	SM_math::vec2 GetMousePosModel() { SetMousePosModel();  return posModel; }

	void PrintMousePosAbs();
	void PrintMousePosModel();
	void PrintMousePosViewport();

	void GetProjectionMatrix(SM_math::mat4 _projMat);

	bool IsMouseOnWindow(SM_math::vec2 windowSize, SM_math::vec2 windowPos);
};


