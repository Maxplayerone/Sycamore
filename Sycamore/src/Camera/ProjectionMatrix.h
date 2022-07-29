#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"


/*glm::mat4 projMat = glm::mat4(1.0f);
    projMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);*/

class ProjectionMatrix {
private:
    glm::mat4 m_matrix;
    float rightBorder;
    float leftBorder;
    float topBorder;
    float bottomBorder;

public:

    ProjectionMatrix(float horizontal, float vertical) {
        rightBorder = horizontal;
        leftBorder = rightBorder * -1;
        topBorder = vertical;
        bottomBorder = topBorder * -1;

        m_matrix = glm::ortho(leftBorder, rightBorder, bottomBorder, topBorder, -1.0f, 1.0f);
    }

    ProjectionMatrix(float left, float right, float top, float bottom) {
        rightBorder = right;
        leftBorder = left;
        topBorder = top;
        bottomBorder = bottom;

        m_matrix = glm::ortho(leftBorder, rightBorder, bottomBorder, topBorder, -1.0f, 1.0f);
    }

    ProjectionMatrix(float left, float right, float vertical) {
        rightBorder = right;
        leftBorder = left;
        topBorder = vertical;
        bottomBorder = topBorder * -1;

        m_matrix = glm::ortho(leftBorder, rightBorder, bottomBorder, topBorder, -1.0f, 1.0f);

    }
    //fix it some day because now I don't want to do it lol
    /*
    ProjectionMatrix(float horizontal, float top, float bottom) {
        rightBorder = horizontal;
        leftBorder = horizontal * -1;
        topBorder = top;
        leftBorder = bottom;

        m_matrix = glm::ortho(leftBorder, rightBorder, bottomBorder, topBorder, -1.0f, 1.0f);
    }
    */

    ProjectionMatrix(float value) {
        rightBorder = topBorder = value;
        leftBorder = bottomBorder = rightBorder * -1;

        m_matrix = glm::ortho(leftBorder, rightBorder, bottomBorder, topBorder, -1.0f, 1.0f);
    }

    ProjectionMatrix()
        : leftBorder(0), rightBorder(0), topBorder(0), bottomBorder(0)
    {
        m_matrix = glm::mat4(1.0f);
    }

    glm::mat4 GetProjectionMatrix() {
        return m_matrix;
    }
};
