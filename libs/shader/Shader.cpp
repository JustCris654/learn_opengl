#include "Shader.hpp"
#include <stdexcept>

std::string Shader::loadShaderAsString(const char *filename) {
    std::string source("");
    std::string line;

    std::ifstream file(filename, std::fstream::in);
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

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

    std::string vertexSource;
    std::string fragmentSource;

    try {
        vertexSource = loadShaderAsString(vertexPath);
        fragmentSource = loadShaderAsString(fragmentPath);
    } catch (std::runtime_error e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ -> " << e.what()
                  << std::endl;
    }
}
