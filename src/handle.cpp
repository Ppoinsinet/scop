#include "scop.hpp"

extern std::vector<Vector3<GLfloat>> vertices;
extern Matrix<4, 1, GLfloat> position;

void onPress(Window<ObjParser *> *win, ObjParser *data, int key) {
    (void)win;
    (void)data;
    static float val = 0.02;

    if (key == GLFW_KEY_RIGHT) {
        for (size_t i = 0; i < vertices.size(); i++)
            position.data[0] += val;
    }
    else if (key == GLFW_KEY_LEFT) {
        for (size_t i = 0; i < vertices.size(); i++)
            position.data[0] -= val;
    }
    else if (key == GLFW_KEY_UP) {
        for (size_t i = 0; i < vertices.size(); i++)
            position.data[1] += val;
    }
    else if (key == GLFW_KEY_DOWN) {
        for (size_t i = 0; i < vertices.size(); i++)
            position.data[1] -= val;
    }
    else if (key == GLFW_KEY_W) {
        for (size_t i = 0; i < vertices.size(); i++)
            position.data[2] += val;
    }
    else if (key == GLFW_KEY_S) {
        for (size_t i = 0; i < vertices.size(); i++)
            position.data[2] -= val;
    } else
        return ;
    // scale += 0.22;
    std::cout << "press :\n" << position << "\n";
}