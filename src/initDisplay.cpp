#include "scop.hpp"

extern std::vector<Vector3<GLfloat> > vertices;
extern std::vector<unsigned int> indices;

void onInit(Window<ObjParser *> *win, ObjParser *data) {
    (void)win;
    (void)data;


    vertices = data->vertices;

    for (size_t i = 0; i < data->faces.size(); i++) {
        for (int k = 0; k < 3; k++) {

            indices.push_back(data->faces[i].verticesIndex[k]);
        }
    }
    std::cout << "onInit : " << vertices.size() << " et " << indices.size() << "\n";

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}