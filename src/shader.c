#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string.h>


Shader create_shader(const char* vertexPath, const char* fragmentPath) {
    Shader shader;
    // 1. Retrieve shader code from files
    FILE* vShaderFile = fopen(vertexPath, "rb");
    FILE* fShaderFile = fopen(fragmentPath, "rb");

    if (!vShaderFile || !fShaderFile) {
        printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
        exit(EXIT_FAILURE);
    }

    // Get file sizes
    fseek(vShaderFile, 0, SEEK_END);
    long vShaderSize = ftell(vShaderFile);
    rewind(vShaderFile);

    fseek(fShaderFile, 0, SEEK_END);
    long fShaderSize = ftell(fShaderFile);
    rewind(fShaderFile);

    // Allocate buffers
    char* vertexCode = (char*)malloc(vShaderSize + 1);
    char* fragmentCode = (char*)malloc(fShaderSize + 1);

    // Read files
    fread(vertexCode, 1, vShaderSize, vShaderFile);
    fread(fragmentCode, 1, fShaderSize, fShaderFile);
    vertexCode[vShaderSize] = '\0';
    fragmentCode[fShaderSize] = '\0';

    fclose(vShaderFile);
    fclose(fShaderFile);

    // 2. Compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char* const*)&vertexCode, NULL);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char* const*)&fragmentCode, NULL);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");

    // Shader program
    shader.ID = glCreateProgram();
    glAttachShader(shader.ID, vertex);
    glAttachShader(shader.ID, fragment);
    glLinkProgram(shader.ID);
    check_compile_errors(shader.ID, "PROGRAM");

    // Delete the shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertexCode);
    free(fragmentCode);

    return shader;
}

void shader_use(Shader* shader) {
    glUseProgram(shader->ID);
}

void shader_set_bool(Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}
void shader_set_int(Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void shader_set_float(Shader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void check_compile_errors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];
    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
}
