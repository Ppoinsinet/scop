#include "scop.hpp"

#define WINDOW_HEIGHT 150
#define WINDOW_WIDTH 600

#include <math.h>
#include "VAO.hpp"
#include "Scene.hpp"

Matrix<4, 1, GLfloat> position;
std::vector<unsigned int> indices;

void initWindow(Window<Scene> *win) {
    win->keyHandle[GLFW_KEY_UP] = onPress;
    win->keyHandle[GLFW_KEY_DOWN] = onPress;
    win->keyHandle[GLFW_KEY_RIGHT] = onPress;
    win->keyHandle[GLFW_KEY_LEFT] = onPress;

    win->keyHandle[GLFW_KEY_A] = onPress;
    win->keyHandle[GLFW_KEY_D] = onPress;
    win->keyHandle[GLFW_KEY_W] = onPress;
    win->keyHandle[GLFW_KEY_S] = onPress;

    win->keyHandle[GLFW_KEY_K] = onPress;

    win->fpsLimit = 60;
    win->width = WINDOW_WIDTH;
    win->cursor.hidden = true;
    win->cursor.centered = true;
    win->cursor.onMouvement = Scene::onMouvement;
}

int main(int ac, char **av) {
    
    printCwd();
    if (ac != 2) {
        std::cerr << "Incorrect input\n";
        exit(1);
    }

    position.Identity();
    Window<Scene> window;

    Scene scene;
    window.data = &scene;
    
    // const GLubyte *i = glGetString(GL_SHADING_LANGUAGE_VERSION);
    // std::cout << "shading language version : " << i << "\n";
    try
    {
        // youtube video : https://www.youtube.com/watch?v=LhQ85bPCAJ8
        initWindow(&window);
        window.create();

        VAO *obj = new VAO(av[1]);
        VAO *obj2 = new VAO("ressources/42.obj");
        scene.listVAO.push_back(obj);
        scene.listVAO.push_back(obj2);

        obj->init();
        obj2->init();

        obj2->position.y = 2;
        obj2->position.x = 2;

        obj2->scale = 0.1f;


        useShaders(&window);

        window.updateFunction = onUpdate;

        window.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}