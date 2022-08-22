#pragma once

#include"../smpch.h"

#include"../Utils/DataTypes.h"

#include"glm/glm.hpp"

struct ShaderSources {
    std::string vertexShader;
    std::string fragmentShader;
};

namespace Shader {

    void UseShader(uint shaderID);
    void UnuseShader();
    uint CreateShader(const std::string& filepath);
    void DeleteShader(uint shaderID);

    void SetUniformMat4f(uint shaderID, const std::string& uniformName, const glm::mat4 matrix);
    void SetUniform1i(uint shaderID, const std::string& name, int value);
    void SetUniform1iv(uint shaderID, const std::string& name);
}
