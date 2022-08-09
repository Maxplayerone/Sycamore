#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"
#include"../Utils/DataTypes.h"

#include"glm/glm.hpp"

struct ShaderSources {
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader {
private:
    uint m_ProgramID;
    std::string m_filepath;

    ShaderSources ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateProgram(const std::string& vertexSource, const std::string& fragmentSource);

    int GetUniformLocation(const std::string& name);
public:
    Shader(std::string filepath);
    ~Shader();

    //binds the shader
    void UseProgram();
    //unbinds the shader
    void UnuseProgram();

    unsigned int GetID() const { return m_ProgramID; }

    //sets four float uniform
    void SetUniformMat4f(const std::string& uniformName, const glm::mat4 matrix);
    //sets one int uniform
    void SetUniform1i(const std::string& name, int value);

    void SetUniform1iv(const std::string& name);
};
