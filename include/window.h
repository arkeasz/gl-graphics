#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

void process_input(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int w, int h);

#endif // WINDOW_H
