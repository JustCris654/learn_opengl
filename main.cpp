#include <assert.h>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *orangeFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char *yellowFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

unsigned int compileShader(GLenum, const char *, std::string name);

unsigned int compileShader(GLenum shaderType, const char *shaderSource,
                           std::string name) {
    // compoile shader
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // check for shader compiler error
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << name << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;

        assert(false);
    }

    return shader;
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

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize glad\n");
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // build and compile shader program
    // ----------------------------------------
    // vertex shader
    unsigned int vertexShader =
        compileShader(GL_VERTEX_SHADER, vertexShaderSource, "VERTEX");

    // fragment shader
    unsigned int orangeFragmentShader = compileShader(
        GL_FRAGMENT_SHADER, orangeFragmentShaderSource, "ORANGE_FRAGMENT");

    unsigned int yellowFragmentShader = compileShader(
        GL_FRAGMENT_SHADER, yellowFragmentShaderSource, "YELLOW_FRAGMENT");

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, orangeFragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int yellowProgram = glCreateProgram();
    glAttachShader(yellowProgram, vertexShader);
    glAttachShader(yellowProgram, yellowFragmentShader);
    glLinkProgram(yellowProgram);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(orangeFragmentShader);

    // set up vertex data
    // buffer data
    // configure vertex attributes

    // float vertices[] = {
    //     0.5f,  0.5f,  0.f, // top right
    //     0.5f,  -0.5f, 0.f, // bottom right
    //     -0.5f, -0.5f, 0.f, // bottom left
    //     -0.5f, 0.5f,  0.f, // top left
    // };

    float first_triangle_vertices[] = {
        -1.f, 0.f, 0.f, // mid left angle
        -1.f, 1.f, 0.f, // top left
        0.f,  0.f, 0.f, // mid
    };

    float second_triangle_vertices[] = {
        0.f, 0.f,  0.f, // mid
        1.f, 0.f,  0.f, // bottom mid
        1.f, -1.f, 0.f, // right bottom
    };

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // bind vertex array object (VAO)
    // then bind and set vertex buffers
    // and then configure vertex attributes

    // setup firts triangle
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle_vertices),
                 first_triangle_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // setup second triangle
    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle_vertices),
                 second_triangle_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

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

        // draw our triangle
        glUseProgram(shaderProgram);
        // with only one VAO it is not necessary to bind it every time
        // but I'll do it for organization
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(yellowProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate all resources
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(1, VBOs);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
