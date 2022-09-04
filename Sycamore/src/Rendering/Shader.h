#pragma once

#include"../smpch.h"

typedef unsigned int uint;

#include"../../Math/SM_math.h"

struct ShaderSources {
    std::string vertexShader;
    std::string fragmentShader;
};

namespace Shader {

    void UseShader(uint id);
    void UnuseShader();
    uint CreateShader(const std::string& filename, int flag);
    void DeleteShader(uint id);

    void SetUniformMat4f(uint id, const std::string& uniformName, const SM_math::mat4 matrix);
    void SetUniform1i(uint id, const std::string& name, int value);
    void SetUniform1iv(uint id, const std::string& name);
}
