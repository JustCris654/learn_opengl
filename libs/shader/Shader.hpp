#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <fstream>
#include <string>
#include <iostream>

class Shader {
  public:
    // constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath);

  public:
    void use(); // use/activate shader
    // utility functions
    void set(const std::string &name, bool value) const;
    void set(const std::string &name, int value) const;
    void set(const std::string &name, float value) const;

  private:
    std::string loadShaderAsString(const char *filename);

  public:
    unsigned int ID; // program ID
};

#endif
