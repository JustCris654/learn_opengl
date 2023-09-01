#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <assert.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "Shader.hpp"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Hello world", nullptr, nullptr);
    if (window == nullptr) {
        printf("Failed to create window\n");
        glfwTerminate();

        return -1;
    }
    int nrAttributes;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize glad\n");
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
              << std::endl;

    // build and compile shader program
    // ----------------------------------------
    // vertex shader
    const std::string vertexFilename(
        "/home/justcris/Documents/cpp/opengl_conan/shaders/vertex_shader.glsl");
    const std::string fragmentFilename(
        "/home/justcris/Documents/cpp/opengl_conan/shaders/frag_shader.glsl");

    Shader shaders(vertexFilename.c_str(), fragmentFilename.c_str());

    // set up vertex data
    // buffer data
    // configure vertex attributes

    float vertices[] = {
        // positions      // colors
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top
        -.5f, -.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.5f, -.5f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom right
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind vertex array object (VAO)
    // then bind and set vertex buffers
    // and then configure vertex attributes

    // setup firts triangle
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // you can unbind also VAO but, as per VBO, it is not necessary
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // float timeValue = glfwGetTime();
        // float greenValue = (std::sin(timeValue) / 2.f) + 0.5f;
        // int vertexColorLocation =
        //     glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // draw our triangle
        shaders.use();
        shaders.set("offSet", 0.5f);
        // with only one VAO it is not necessary to bind it every time
        // but I'll do it for organization
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
