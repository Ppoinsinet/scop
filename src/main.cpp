#include "scop.hpp"

#define WINDOW_HEIGHT 150
#define WINDOW_WIDTH 600

#include <math.h>
#include "VAO.hpp"

Matrix<4, 1, GLfloat> position;
std::vector<unsigned int> indices;

int main(int ac, char **av) {
    
    printCwd();
    if (ac != 2) {
        std::cerr << "Incorrect input\n";
        exit(1);
    }

    position.Identity();
    Window<VAO *> window;

    ObjParser parser(av[1]);
    std::cout << "coucou\n";
    VAO obj(parser);
    window.data = &obj;

    std::cout << obj.vertices.size() << " vertices\n";

    
    // const GLubyte *i = glGetString(GL_SHADING_LANGUAGE_VERSION);
    // std::cout << "shading language version : " << i << "\n";
    try
    {
        // youtube video : https://www.youtube.com/watch?v=LhQ85bPCAJ8

        window.keyHandle[GLFW_KEY_UP] = onPress;
        window.keyHandle[GLFW_KEY_DOWN] = onPress;
        window.keyHandle[GLFW_KEY_RIGHT] = onPress;
        window.keyHandle[GLFW_KEY_LEFT] = onPress;

        window.keyHandle[GLFW_KEY_A] = onPress;
        window.keyHandle[GLFW_KEY_D] = onPress;
        window.keyHandle[GLFW_KEY_W] = onPress;
        window.keyHandle[GLFW_KEY_S] = onPress;

        window.keyHandle[GLFW_KEY_K] = onPress;

        window.fpsLimit = 60;
        window.width = WINDOW_WIDTH;
        window.cursor.hidden = true;
        window.cursor.centered = true;
        window.create();


        useShaders(&window);

        window.updateFunction = onUpdate;

        obj.init();
        std::cout << "hjh\n";
        window.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}