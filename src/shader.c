#include "shader.h"
#include <stdio.h>

Shader create_shader_program(const char* vertex_path, const char* fragment_path) {
    Shader shader;
    char* vertex_code = NULL;
    char* fragment_code = NULL;

    FILE* vertex_file = fopen(vertex_path, "r");
    FILE* fragment_file = fopen(fragment_path, "r");

    
}
