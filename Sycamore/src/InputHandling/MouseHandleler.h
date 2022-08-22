#pragma once

#include"../../Math/SM_math.h"

class MouseHandleler {
private:
	MouseHandleler();
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
	SM_math::vec4 GetMousePosModel();

	void DebugCheckMouesPosAbs();
	void DebugCheckMousePosModel();

	void GetProjectionMatrix(SM_math::mat4& _projMat);
};


