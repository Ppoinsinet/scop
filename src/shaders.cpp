#include "scop.hpp"

#define VERTEX_SHADER_FILEPATH "./vertex.shader"
#define FRAGMENT_SHADER_FILEPATH "./fragment.shader"

void useShaders(Window<int *> *window) {
    // char logs[512];
    int success = 0;

    Shader vertex(VERTEX_SHADER, VERTEX_SHADER_FILEPATH);
    // std::cout << "coucou\n";
    Shader fragment(FRAGMENT_SHADER, FRAGMENT_SHADER_FILEPATH);

    int programId = glCreateProgram();
    glAttachShader(programId, vertex.getId());
    glAttachShader(programId, fragment.getId());
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    // if (!success) {
    //     glGetProgramInfoLog(programId, sizeof(logs), NULL, logs);
    //     throw logs;
    // }

    glUseProgram(programId);
    window->data = &programId;
    std::cout << "Set data = " << programId << "\n";
}