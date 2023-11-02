#include "scop.hpp"

extern std::vector<Vector3<GLfloat> > vertices;
extern Vector3<GLfloat> position;

void onPress(Window<VAO *> *win, VAO *data, int key) {
    (void)win;
    (void)data;
    static float val = 0.02;

    if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
        
        position += win->camera.U * val;
    }
    else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        position -= win->camera.U * val;
    }
    else if (key == GLFW_KEY_UP) {
        position += win->camera.V * val;
    }
    else if (key == GLFW_KEY_DOWN) {
        position -= win->camera.V * val;
    }
    else if (key == GLFW_KEY_W) {
        position += win->camera.N * val;
    }
    else if (key == GLFW_KEY_S) {
        position -= win->camera.N * val;
    } else {
        ObjParser tmp("ressources/42.obj");
        VAO *test = new VAO(tmp);
        test->init();
        win->data = test;
        return ;
    }
    // scale += 0.22;
    std::cout << "press :\n" << position << "\n";
}