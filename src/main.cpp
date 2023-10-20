#include "scop.hpp"

#define WINDOW_HEIGHT 150
#define WINDOW_WIDTH 150

#include <math.h>

Matrix<4, 1, GLfloat> position;
std::vector<Vector3<GLfloat> > vertices;
std::vector<unsigned int> indices;

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Incorrect input\n";
        exit(1);
    }

    position.Identity();

    ObjParser parser(av[1]);
    std::cout << parser.vertices.size() << " vertices\n";

    Window<ObjParser *> window;

    try
    {
        // youtube video : https://www.youtube.com/watch?v=LhQ85bPCAJ8

        // useShaders(&window);
        
        // glEnable(GL_CULL_FACE);
        // glFrontFace(GL_CW);
        // glCullFace(GL_BACK);

        window.data = &parser;
        window.keyHandle[GLFW_KEY_UP] = onPress;
        window.keyHandle[GLFW_KEY_DOWN] = onPress;
        window.keyHandle[GLFW_KEY_RIGHT] = onPress;
        window.keyHandle[GLFW_KEY_LEFT] = onPress;

        window.keyHandle[GLFW_KEY_W] = onPress;
        window.keyHandle[GLFW_KEY_S] = onPress;

        window.fpsLimit = 60;
        window.width = 300;
        window.initFunction = onInit;
        window.create();
        window.updateFunction = onUpdate;

        window.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}