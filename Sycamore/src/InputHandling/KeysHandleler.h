#pragma once
#include"../Utils/DataTypes.h"

class KeyHandleler {
private:
	KeyHandleler();
	const uint keys_count = 350;
public:
	bool* m_keys = new bool[keys_count];

	KeyHandleler(const KeyHandleler&) = delete;
	~KeyHandleler() { delete[] m_keys; }

	static KeyHandleler& Get() {
		static KeyHandleler instance;
		return instance;
	}

	//returns ONCE if the key is pressed 
	bool IsKeyPressed(int key);
	//returns true for as long as the key is pressed
	bool IsKeyHeld(int key);
	int Length() { return keys_count; }
};

