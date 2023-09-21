#ifndef SCOP_HPP
#define SCOP_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <stdexcept>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vertice.hpp"

#include "Face.hpp"
#include "ObjParser.hpp"
#include "Window.hpp"
#include "Shader.hpp"

std::vector<std::string> split (const std::string &s, std::string delim);

#endif