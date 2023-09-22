#include "scop.hpp"

extern std::vector<Vector3<GLfloat>> vertices;
extern Matrix<4, 1, GLfloat> position;

void onPress(Window<ObjParser *> *win, ObjParser *data, int key) {
    (void)win;
    (void)data;
    static float val = 0.02;

    if (key == GLFW_KEY_RIGHT) {
        position.data[0] += val;
    }
    else if (key == GLFW_KEY_LEFT) {
        position.data[0] -= val;
    }
    else if (key == GLFW_KEY_UP) {
        position.data[1] += val;
    }
    else if (key == GLFW_KEY_DOWN) {
        position.data[1] -= val;
    }
    else if (key == GLFW_KEY_W) {
        position.data[2] += val;
    }
    else if (key == GLFW_KEY_S) {
        position.data[2] -= val;
    } else
        return ;
    // scale += 0.22;
    std::cout << "press :\n" << position << "\n";
}