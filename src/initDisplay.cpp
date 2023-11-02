#include "scop.hpp"

extern std::vector<Vector3<GLfloat> > vertices;
extern std::vector<unsigned int> indices;

void onInit(Window<VAO *> *win, VAO *data) {
    (void)win;
    (void)data;

    std::cout << "onInit : " << data->vertices.size() << " et " << data->indices.size() << "\n";

}