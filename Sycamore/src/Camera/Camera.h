#pragma once

//glm
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"../Shadering/Shader.h"

class Camera {
private:
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;
public:
	enum class MatrixType { TYPE_MODEL, TYPE_VIEW, TYPE_PROJECTION };

	Camera(Shader& shaderProgram) {
		modelMat = glm::mat4(1.0f);
		viewMat = glm::mat4(1.0f);
		projMat = glm::mat4(1.0f);

		shaderProgram.SetUniformMat4f("model", modelMat);
		shaderProgram.SetUniformMat4f("view", viewMat);
		shaderProgram.SetUniformMat4f("projection", projMat);
	}

	void Push(MatrixType type, glm::mat4 matrix, Shader& shaderProgram) {
		switch (type) {
		case MatrixType::TYPE_MODEL:
			modelMat = matrix;
			shaderProgram.SetUniformMat4f("model", modelMat);
			break;
		case MatrixType::TYPE_VIEW:
			viewMat = matrix;
			shaderProgram.SetUniformMat4f("view", viewMat);
			break;
		case MatrixType::TYPE_PROJECTION:
			projMat = matrix;
			shaderProgram.SetUniformMat4f("projection", projMat);
			break;
		}
	}

	void Update(Shader& shaderProgram) {
		shaderProgram.SetUniformMat4f("model", modelMat);
		shaderProgram.SetUniformMat4f("view", viewMat);
		shaderProgram.SetUniformMat4f("projection", projMat);
	}
};
