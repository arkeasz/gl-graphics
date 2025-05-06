#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string.h>

typedef struct {
    unsigned int id;
} Shader;

Shader create_shader_program(const char* vertex_path, const char* fragment_path);
void use_shader(Shader shader);
void delete_shader(Shader shader);

void set_shader_uniform_int(Shader shader, const char* name, int value);
void set_shader_uniform_float(Shader shader, const char* name, float value);
void set_shader_uniform_bool(Shader shader, const char* name, int value);

const char *vertex_shader_source ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char *fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"uniform float timeValue;\n"
"void main()\n"
"{\n"
"    float factor = sin(timeValue) * 0.5 + 0.5;\n"
"    vec3 animatedColor = ourColor * factor;\n"
"    FragColor = vec4(animatedColor, 1.0f);\n"
"}\n\0";


#endif // SHADER_H
