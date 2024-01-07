#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vector4.hpp"

class Light {
public:
    Vector4<float> colors;
protected:
    Light() {}
};

#endif