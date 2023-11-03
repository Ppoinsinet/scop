#ifndef SCOP_HPP
#define SCOP_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <stdexcept>
#include <unistd.h>

#include <math.h>


#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <GL/gl.h>

#include "stb_image.h"
#include "Matrix.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

#include "Quaternion.hpp"
template <typename T>
Vector3<T> rotate(float angle, const Vector3<T> &a, const Vector3<T> &b) {
    Quaternion rota(angle, b);

    Quaternion conjugate = rota.conjugate();

    Quaternion w = rota * a * conjugate;

    return Vector3<T>(w.x, w.y, w.z);
}

#include "Face.hpp"
#include "ObjParser.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "Scene.hpp"

#include "Camera.hpp"


std::vector<std::string> split (const std::string &s, std::string delim);

void onPress(Window<Scene> *win, Scene *data, int key);
void onUpdate(Window<Scene> *win, Scene *data);


#define VERTEX_SHADER_FILEPATH "./vertex.shader"
#define FRAGMENT_SHADER_FILEPATH "./fragment.shader"
void printCwd(void);

extern GLuint gWorldLocation;
extern GLuint gSamplerLocation;

template <class T>
void useShaders(Window<T> *window) {
    (void)window;
    char logs[512];
    int success = 0;
        printCwd();
    Shader vertex(VERTEX_SHADER, VERTEX_SHADER_FILEPATH);
    Shader fragment(FRAGMENT_SHADER, FRAGMENT_SHADER_FILEPATH);

    int programId = glCreateProgram();
    vertex.programId = programId;
    fragment.programId = programId;

    glAttachShader(programId, vertex.getId());
    glAttachShader(programId, fragment.getId());
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programId, sizeof(logs), NULL, logs);
        std::cout << "error : " << logs << "\n";
        throw logs;
    }

    glUseProgram(programId);

    gWorldLocation = glGetUniformLocation(programId, "gWorld");
    gSamplerLocation = glGetUniformLocation(programId, "gSampler");
    
}

std::vector<Vector3<GLfloat> > &verticesOperations(std::vector<Vector3<GLfloat> > &vertices);


#endif