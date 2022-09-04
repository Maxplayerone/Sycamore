#pragma once
#include"../smpch.h"
class GameObject;
class LevelEditorScene;

namespace SM_Serializer {

	void Serialize();
	bool Deserialize(LevelEditorScene* scene);
	void Push(GameObject go);
}