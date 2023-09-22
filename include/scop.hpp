#ifndef SCOP_HPP
#define SCOP_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <stdexcept>

#include <math.h>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/gl.h>


#include "Matrix.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

#include "Face.hpp"
#include "ObjParser.hpp"
#include "Window.hpp"
#include "Shader.hpp"

std::vector<std::string> split (const std::string &s, std::string delim);

void onPress(Window<ObjParser *> *win, ObjParser *data, int key);


void onInit(Window<ObjParser *> *win, ObjParser *data);
void onUpdate(Window<ObjParser *> *win, ObjParser *data);


#define VERTEX_SHADER_FILEPATH "./vertex.shader"
#define FRAGMENT_SHADER_FILEPATH "./fragment.shader"

template <class T>
void useShaders(Window<T> *window) {
    (void)window;
    char logs[512];
    int success = 0;

    Shader vertex(VERTEX_SHADER, VERTEX_SHADER_FILEPATH);
    Shader fragment(FRAGMENT_SHADER, FRAGMENT_SHADER_FILEPATH);

    int programId = glCreateProgram();
    glAttachShader(programId, vertex.getId());
    glAttachShader(programId, fragment.getId());
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programId, sizeof(logs), NULL, logs);
        throw logs;
    }

    glUseProgram(programId);
}

std::vector<Vector3<GLfloat>> &verticesOperations(std::vector<Vector3<GLfloat>> &vertices);


#endif