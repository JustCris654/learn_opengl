#include "Shader.hpp"

std::string Shader::loadShaderAsString(const char *filename) {
    std::string source("");
    std::string line;

    std::ifstream file(filename, std::fstream::in);
    std::cout << "File " << filename <<"  is open: " << file.is_open() << std::endl;
    if (file.is_open()) {
        source = std::string(std::istreambuf_iterator<char>(file),
                             std::istreambuf_iterator<char>());
    } else {
        std::string error =
            std::string("Could not open file: ").append(filename);
        throw std::runtime_error(error);
    }

    return source;
}

unsigned int Shader::compileShader(GLenum shaderType, const char *shaderSource,
                                   std::string name) {
    // compile shader
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // check for shader compiler error
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << name << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;

        // exit program if shader compilation failed
        assert(false);
    }

    return shader;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

    // 1. get shaders source code from file
    std::string vertexSource;
    std::string fragmentSource;

    try {
        vertexSource = loadShaderAsString(vertexPath);
        fragmentSource = loadShaderAsString(fragmentPath);
    } catch (std::runtime_error e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ -> " << e.what()
                  << std::endl;

        assert(false && "Could not read file");
    }

    // 2. compile shaders
    unsigned int vertex, fragment;

    vertex = compileShader(GL_VERTEX_SHADER, vertexSource.c_str(), "VERTEX");
    fragment =
        compileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str(), "FRAGMENT");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);

    // print linking errors if any
    int success;
    char infoLog[512];
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl
                  << infoLog << std::endl;

        // exit program if linking failed
        assert(false);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(this->ID);
}

void Shader::use() { glUseProgram(this->ID); }

void Shader::set(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}
void Shader::set(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::set(const std::string &name, float value) const {
    std::cout << "Set float uniform " << name << std::endl;
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
