#include "scop.hpp"

#define WINDOW_HEIGHT 150
#define WINDOW_WIDTH 600

#include <math.h>

Matrix<4, 1, GLfloat> position;
std::vector<Vector3<GLfloat> > vertices;
std::vector<unsigned int> indices;

GLuint gWorldLocation;

int main(int ac, char **av) {
        printCwd();
    if (ac != 2) {
        std::cerr << "Incorrect input\n";
        exit(1);
    }

    position.Identity();

    ObjParser parser(av[1]);
    std::cout << parser.vertices.size() << " vertices\n";

    Window<ObjParser *> window;
    
    // const GLubyte *i = glGetString(GL_SHADING_LANGUAGE_VERSION);
    // std::cout << "shading language version : " << i << "\n";
    try
    {
        // youtube video : https://www.youtube.com/watch?v=LhQ85bPCAJ8

        window.data = &parser;
        window.keyHandle[GLFW_KEY_UP] = onPress;
        window.keyHandle[GLFW_KEY_DOWN] = onPress;
        window.keyHandle[GLFW_KEY_RIGHT] = onPress;
        window.keyHandle[GLFW_KEY_LEFT] = onPress;

        window.keyHandle[GLFW_KEY_W] = onPress;
        window.keyHandle[GLFW_KEY_S] = onPress;

        window.fpsLimit = 60;
        window.width = WINDOW_WIDTH;
        window.initFunction = onInit;
        window.cursor.hidden = true;
        window.cursor.centered = false;
        window.create();

        useShaders(&window);

        window.updateFunction = onUpdate;

        window.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}