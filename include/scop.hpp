#ifndef SCOP_HPP
#define SCOP_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Vertice.hpp"
#include "Face.hpp"
#include "IVector2.hpp"
#include "ObjParser.hpp"
#include "Window.hpp"

std::vector<std::string> split (const std::string &s, std::string delim);

#endif