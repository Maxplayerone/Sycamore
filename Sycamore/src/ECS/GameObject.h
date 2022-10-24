#pragma once
#include"Component.h"
#include"../Utils/Logger.h"

#include<xhash>

typedef unsigned int uint;

class GameObject {
private:
	std::vector<Component*> m_components;

	std::string m_name;

	template<typename Base, typename T>
	inline bool Instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	uint64_t m_uuid;
	//id given by the batch renderer
	//that is the same as the position of the object
	//in that batch's array
	int m_rendererID = 0;

	std::string GetRandomName();
public:

	GameObject();
	GameObject(const std::string& name);
	GameObject(const std::string& name, uint64_t _uuid);
	GameObject(uint64_t _uuid);

	//adds a component to the game object
	template<typename T>
	int AddComponent(T* component) {
		if (!Instanceof<Component>(component)) {
			LOGGER_ERROR("You need to pass a derived class of component");
			return -1;
		}
		if (std::find(m_components.begin(), m_components.end(), component) != m_components.end()) {
			LOGGER_ERROR("An object cannot have more than one component of the same type");
			return -1;
		}

		m_components.push_back(component);
		return 0;
	}

	//returns a component from the game object
	template<typename ComponentType>
	ComponentType* GetComponent() {
		for (unsigned int i = 0; i < m_components.size(); i++) {
			if (ComponentType* cmp = dynamic_cast<ComponentType*>(m_components[i])) {
				return cmp;
			}
		}
		return nullptr;
	}

	//removes component from m_components vector and returns it
	template<typename ComponentType>
	ComponentType* RemoveComponent() {
		for (unsigned int i = 0; i < m_components.size(); i++) {
			if (ComponentType* cmp = dynamic_cast<ComponentType*>(m_components[i])) {
				ComponentType* cmpCpy = cmp;

				m_components.erase(m_components.begin() + i);
				std::stringstream ss;
				ss << "m_components length " << m_components.size();
				LOGGER_INFO(ss.str());
				return cmpCpy;
			}
		}
	}

	void Update(float deltaTime);
	void ImGui();

	uint64_t GetID() const { return m_uuid; }

	std::string GetName() { return m_name; }

	void SetRendererID(int id) { m_rendererID = id; }
	int GetRendererID() const { return m_rendererID; }

	void Destroy();
};
