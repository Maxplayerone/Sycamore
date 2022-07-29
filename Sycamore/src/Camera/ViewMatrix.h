#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class ViewMatrix {
private:
	glm::mat4 m_matrix;
public:
	ViewMatrix() {
		m_matrix = glm::mat4(1.0f);
	}

	glm::mat4 GetViewMatrix() {
		return m_matrix;
	}
};