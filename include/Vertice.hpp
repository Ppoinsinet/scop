#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <GL/gl.h>
#include "Vector3.hpp"

class Vertice: public Vector3<GLfloat> {

public:

    Vertice() : Vector3<GLfloat>(0,0,0) {}
    Vertice(float x, float y, float z);
};

#endif