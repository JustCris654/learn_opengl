#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

class Shader {
  public:
    // constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

  public:
    void use(); // use/activate shader
    // utility functions
    void set(const std::string &name, bool value) const;
    void set(const std::string &name, int value) const;
    void set(const std::string &name, float value) const;

  private:
    std::string loadShaderAsString(const char *filename);
    unsigned int compileShader(GLenum shaderType, const char *shaderSource,
                               std::string name);

  private:
    unsigned int ID; // program ID
};
#endif
