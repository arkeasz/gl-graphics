#include <stdio.h>
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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

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

    // -- Vertex Shader -- //
    /*
        this is base in the normalized device coordinates (NDC)
        the coordinates are in the range of -1.0 to 1.0
        this ignoring the z axis, so the triangle is flat on the screen
    */
    // float vertices[] = {
    //     // first triangle
    //     0.5f,  0.5f, 0.0f, // top right
    //     0.5f, -0.5f, 0.0f, // bottom right
    //    -0.5f,  0.5f, 0.0f, // top left
    //     // second triangle
    //     0.5f, -0.5f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f  // top left
    // };
    float vertices[] = {

       // positions        // colors
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // top left
    };

    // so the vertex now is [x, y, z, r, g, b]

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    /*
        ¿What is a buffer?
        a buffer is a region of memory that is used to store temporary data,
        such as the vertices of a 3D object. In OpenGL, buffers are used to
        store the vertices, indices, and other data that are used to render
        3D objects. Buffers can be created, bound, and used to send data to
        the GPU. The data is stored in the GPU memory, and the CPU can access
        the data using the buffer object. The buffer object is a handle to the
        buffer in the GPU memory. The buffer object is created using the
        glGenBuffers function, and the data is sent to the GPU using the
        glBufferData function. The buffer object is bound to a target using
        the glBindBuffer function. The target is the type of buffer that is
        being used, such as GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER.
    */



    unsigned int vertex_shader;

    // create a vertex shader object
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    // set the source code for the vertex shader
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    // compile the vertex shader
    glCompileShader(vertex_shader);

    int success;
    char infoLog[512];
    // check for compilation errors
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    // get the error log
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        fprintf(stderr, "Error: not able to compile the vertex shader\n%s\n", infoLog);
    }

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); // create a fragment shader object
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL); // set the source code for the fragment shader
    glCompileShader(fragment_shader); // compile the fragment shader

    unsigned int shader_program;
    shader_program = glCreateProgram(); // create a shader program object

    glAttachShader(shader_program, vertex_shader); // attach the vertex shader to the program
    glAttachShader(shader_program, fragment_shader); // attach the fragment shader to the program
    glLinkProgram(shader_program); // link the program

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success); // check for linking errors
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog); // get the error log
        fprintf(stderr, "Error: no se pudo enlazar el shader program\n%s\n", infoLog);
    }

    glDeleteShader(vertex_shader); // delete the vertex shader object
    glDeleteShader(fragment_shader); // delete the fragment shader object


    unsigned int VAO;
    unsigned int EBO;
    unsigned int VBO;

    /*
        first: VAO, because it stores the state of the vertex attributes
        second: VBO,
    */

    // -- VAO -- //
    glGenVertexArrays(1, &VAO); // generate a vertex array object
    glBindVertexArray(VAO); // bind the vertex array object

    // -- VBO -- //
    glGenBuffers(1, &VBO); // generate a buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer object to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send the data to the GPU

    // -- EBO -- //
    glGenBuffers(1, &EBO); // generate a buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind the buffer object to the GL_ELEMENT_ARRAY_BUFFER target
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // send the data to the GPU

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // set the vertex attribute pointer
    glEnableVertexAttribArray(0); // enable the vertex attribute array


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // set the vertex attribute pointer
    glEnableVertexAttribArray(0); // enable the vertex attribute array

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float))); // set the vertex attribute pointer
    glEnableVertexAttribArray(1); // enable the vertex attribute array

    while(!glfwWindowShouldClose(window)) {
        // -- Input -- //
        process_input(window);

        // -- Style -- //
        glClearColor(0.8f, 0.8f, 0.8f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);


        // -- Render -- //
        glUseProgram(shader_program); // use the shader program
        glBindVertexArray(VAO); // bind the vertex array object
        // glDrawArrays(GL_TRIANGLES, 0, 3); // draw the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw the triangle using the element buffer object

        // -- Bind the shader program -- //
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // -- Dealocate -- //
    glDeleteVertexArrays(1, &VAO); // delete the vertex array object
    glDeleteBuffers(1, &VBO); // delete the buffer object
    glDeleteBuffers(1, &EBO); // delete the buffer object
    glDeleteProgram(shader_program); // delete the shader program object

    glfwTerminate();
    return 0;
}
