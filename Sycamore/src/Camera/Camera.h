#pragma once

//glm
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"../Rendering/Shader.h"

class Camera {
private:
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;
public:
	enum class MatrixType { TYPE_MODEL, TYPE_VIEW, TYPE_PROJECTION };

	Camera(uint shaderID) {
		modelMat = glm::mat4(1.0f);
		viewMat = glm::mat4(1.0f);
		projMat = glm::mat4(1.0f);

		Shader::SetUniformMat4f(shaderID, "model", modelMat);
		Shader::SetUniformMat4f(shaderID, "view", viewMat);
		Shader::SetUniformMat4f(shaderID, "projection", projMat);
	}

	void Push(MatrixType type, glm::mat4 matrix, uint shaderID) {
		switch (type) {
		case MatrixType::TYPE_MODEL:
			modelMat = matrix;
			Shader::SetUniformMat4f(shaderID, "model", modelMat);
			break;
		case MatrixType::TYPE_VIEW:
			viewMat = matrix;
			Shader::SetUniformMat4f(shaderID, "view", viewMat);
			break;
		case MatrixType::TYPE_PROJECTION:
			projMat = matrix;
			Shader::SetUniformMat4f(shaderID, "projection", projMat);
			break;
		}
	}

	void Update(uint shaderID) {
		Shader::SetUniformMat4f(shaderID, "model", modelMat);
		Shader::SetUniformMat4f(shaderID, "view", viewMat);
		Shader::SetUniformMat4f(shaderID, "projection", projMat);
	}
};
