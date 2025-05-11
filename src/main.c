#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "window.h"
#include "shader.h"

/*
    This is a simple OpenGL program that creates a window and sets up a basic
    rendering loop. It initializes GLFW, creates a window, and sets up an OpenGL
    context using GLAD. The program also includes a vertex shader and a fragment
    shader, compiles them, and links them into a shader program. The main loop
    clears the screen and draws a triangle using the shader program.
*/

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Error: no se pudo inicializar GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    #endif

    // to create a window and OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Model shader", NULL, NULL);

    if (!window) {
        fprintf(stderr, "Error: no se pudo crear la ventana\n");
        glfwTerminate();
        return -1;
    }

    // create context
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Error: no se pudo cargar GLAD\n");
        glfwTerminate();
        return -1;
    }

    // polygon mode, decomment the next line to see the wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, 640, 480);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        // positions         // colors
        // x     y     z     // r     g     b
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };


    Shader model_shader = create_shader("/home/arki/graphics/shaders/model.vs", "/home/arki/graphics/shaders/model.fs");

    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO); // generate a vertex array object
    glGenBuffers(1, &VBO); // generate a buffer object

    glBindVertexArray(VAO); // bind the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer object to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send the data to the GPU

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // set the vertex attribute pointer
    glEnableVertexAttribArray(0); // enable the vertex attribute array

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float))); // set the vertex attribute pointer
    glEnableVertexAttribArray(1); // enable the vertex attribute array

    while(!glfwWindowShouldClose(window)) {
        // -- Input -- //
        process_input(window);

        // -- Style -- //
        glClearColor(0.4, 0.4, 0.4, 0.5f); // set the clear color
        glClear(GL_COLOR_BUFFER_BIT);

        shader_use(&model_shader); // use the shader program
        glBindVertexArray(VAO); // bind the vertex array object
        glDrawArrays(GL_TRIANGLES, 0, 3); // draw the triangle

        // -- Bind the shader program -- //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // -- Dealocate -- //
    glDeleteVertexArrays(1, &VAO); // delete the vertex array object
    glDeleteBuffers(1, &VBO); // delete the buffer object

    glfwTerminate();
    return 0;
}
