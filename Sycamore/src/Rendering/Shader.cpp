#include"Shader.h"

#include"../Utils/ErrorHandling.h"
#include"../Utils/Logger.h"

Shader::Shader(std::string filepath)
    : m_ProgramID(0), m_filepath(filepath)
{
    ShaderSources sources = ParseShader(m_filepath);
    m_ProgramID = CreateProgram(sources.vertexShader, sources.fragmentShader);

    GLCall(glUseProgram(m_ProgramID));
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_ProgramID));
}

void Shader::UseProgram() {
    //std::cout << "Program id " << m_ProgramID << std::endl;
    GLCall(glUseProgram(m_ProgramID));
}

void Shader::UnuseProgram() {
    GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name) {

    GLCall(int uniLocation = glGetUniformLocation(m_ProgramID, name.c_str()));
    if (uniLocation == -1) {
        std::stringstream ss;
        ss << "No active uniform with name " << name;
        LOGGER_WARNING(ss.str());
    }

    return uniLocation;
}

void Shader::SetUniformMat4f(const std::string& uniformName, glm::mat4 matrix) {
    glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(const std::string& name) {
    int location = GetUniformLocation(name.c_str());
    int sampler[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    GLCall(glUniform1iv(location, 8, sampler));
}

ShaderSources Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    if (stream.fail()) {
        std::stringstream ss;
        ss << "Cannot open the shader file with the path " << filepath;
        LOGGER_ERROR(ss.str());
        ASSERT(false);
    }

    enum class SHADERTYPE { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    std::stringstream sources[2];
    SHADERTYPE type = SHADERTYPE::NONE;

    std::string line;
    while (getline(stream, line)) {

        if (line.find("#type") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = SHADERTYPE::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = SHADERTYPE::FRAGMENT;
            }
        }
        else {
            sources[(int)type] << line << '\n';
        }
    }
    return { sources[0].str(), sources[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_TRUE) return id;

    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    char* message = (char*)malloc(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    //it throws an error for some reason idk why
    /*
    std::stringstream _ss;
    _ss << "Failed to compile the shader " << message;
    LOGGER_ERROR(_ss);
    */
    free(message);
    return 0;
}

unsigned int Shader::CreateProgram(const std::string& vertexSource, const std::string& fragmentSource) {
    unsigned int program = glCreateProgram();
    unsigned int vertexSh = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentSh = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vertexSh);
    glAttachShader(program, fragmentSh);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexSh);
    glDeleteShader(fragmentSh);

    return program;
}
