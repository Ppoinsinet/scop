#include "scop.hpp"

#include "Scene.hpp"

extern std::vector<Vector3<GLfloat> > vertices;

void onPress(Window<Scene> *win, Scene *data, int key) {
    (void)win;
    (void)data;
    static float val = 0.02;

    Matrix<3, 3, float> rotatedVectors = data->camera.getRotatedVectors();


    if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
        
        data->camera.position += rotatedVectors.getColumn(0) * val;
    }
    else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        data->camera.position -= rotatedVectors.getColumn(0) * val;
    }
    else if (key == GLFW_KEY_UP) {
        data->camera.position += rotatedVectors.getColumn(1) * val;
    }
    else if (key == GLFW_KEY_DOWN) {
        data->camera.position -= rotatedVectors.getColumn(1) * val;
    }
    else if (key == GLFW_KEY_W) {
        data->camera.position += rotatedVectors.getColumn(2) * val;
    }
    else if (key == GLFW_KEY_S) {
        data->camera.position -= rotatedVectors.getColumn(2) * val;
    } else
        return ;
    // scale += 0.22;
}