#include"GameObject.h"

#include"../smpch.h"

#include"../Utils/UUID.h"


GameObject::GameObject() {
	m_uuid = SM_UUID::GetUUID();
	m_name = GetRandomName();
}

GameObject::GameObject(const std::string& name) {
	m_uuid = SM_UUID::GetUUID();
	m_name = name;
}

GameObject::GameObject(const std::string& name, uint64_t _uuid) {
	m_uuid = _uuid;
	m_name = name;
}

GameObject::GameObject(uint64_t _uuid) {
	m_uuid = _uuid;
	m_name = GetRandomName();
}


void GameObject::Update(float deltaTime) {
	for (int i = 0; i < m_components.size(); i++) {
		m_components[i]->Update(deltaTime);
	}
}

void GameObject::ImGui() {
	ImGui::Begin("GameObject");

	//aligning the text in the center
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(m_name.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(m_name.c_str());

	for (auto component : m_components) {
		component->ImGui();
	}

	ImGui::End();
}

std::string GameObject::GetRandomName() {
	std::string randomNames[15] = {
		"Stichology",
		"B3astlyboy7Vahana",
	"Vahanaknight959",
	"Illuvium",
	"Proctor",
	"Ventorious",
	"Irresiant",
	"Aquifer",
	"Linonophobia",
	"Togated",
	"Shananigans",
	"Ridotto",
	"Vendemmia",
	"Pro4minMomus",
	"Momustow99"
	};

	int randNum = rand() % 15;
	return randomNames[randNum];
}

void GameObject::Destroy() {
}