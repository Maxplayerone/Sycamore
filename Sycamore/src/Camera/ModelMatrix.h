#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"


class ModelMatrix {
private:
    glm::mat4 m_matrix;
public:
    enum class COORDINATE {X, Y, Z};

    ModelMatrix() {
        m_matrix = glm::mat4(1.0f);
    }

    ModelMatrix(float rotation, COORDINATE coordValue) {
        switch (coordValue) {
        case COORDINATE::X:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
        case COORDINATE::Y:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
        case COORDINATE::Z:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        default:
            m_matrix = glm::mat4(1.0f);
            break;
        }
    }

    ModelMatrix(float scaleArray[3]) {
        m_matrix = glm::scale(m_matrix, glm::vec3(scaleArray[0], scaleArray[1], scaleArray[2]));
    }

    ModelMatrix(float scaleValue) {
        m_matrix = glm::scale(m_matrix, glm::vec3(scaleValue, scaleValue, scaleValue));
    }

    ModelMatrix(float rotation, COORDINATE coordValue, float scaleValue) {
        switch (coordValue) {
        case COORDINATE::X:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
            m_matrix = glm::scale(m_matrix, glm::vec3(scaleValue, scaleValue, scaleValue));
            break;
        case COORDINATE::Y:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            m_matrix = glm::scale(m_matrix, glm::vec3(scaleValue, scaleValue, scaleValue));
            break;
        case COORDINATE::Z:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            m_matrix = glm::scale(m_matrix, glm::vec3(scaleValue, scaleValue, scaleValue));
            break;
        default:
            m_matrix = glm::mat4(1.0f);
            break;
        }
    }

    ModelMatrix(float rotation, COORDINATE coordValue, float scaleArray[3]) {
        switch (coordValue) {
        case COORDINATE::X:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
            m_matrix = glm::scale(m_matrix, glm::vec3(scaleArray[0], scaleArray[1], scaleArray[2]));
            break;
        case COORDINATE::Y:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            m_matrix = glm::scale(m_matrix, glm::vec3(scaleArray[0], scaleArray[1], scaleArray[2]));
            break;
        case COORDINATE::Z:
            m_matrix = glm::rotate(m_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            m_matrix = glm::scale(m_matrix, glm::vec3(scaleArray[0], scaleArray[1], scaleArray[2]));
            break;
        default:
            m_matrix = glm::mat4(1.0f);
            break;
        }
    }

    glm::mat4 GetModelMatrix() {
        return m_matrix;
    }
};