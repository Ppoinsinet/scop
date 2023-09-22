#include "scop.hpp"

extern std::vector<Vector3<GLfloat>> vertices;
extern std::vector<unsigned int> indices;

void onInit(Window<ObjParser *> *win, ObjParser *data) {
    (void)win;
    (void)data;

    // for (size_t i = 0; i < data->vertices.size(); i++) {
    //     vertices.push_back(data->vertices[i]);
    // }

    // for (size_t i = 0; i < data->faces.size(); i++) {
    //     for (int k = 0; k < 3; k++) {

    //         indices.push_back(data->faces[i].verticesIndex[k]);
    //     }
    // }

    vertices.push_back(Vector3<GLfloat>(0.5f, 0.5f, 0.5f));
    vertices.push_back(Vector3<GLfloat>(-0.5f, 0.5f, -0.5f));
    vertices.push_back(Vector3<GLfloat>(-0.5f, 0.5f, 0.5f));
    vertices.push_back(Vector3<GLfloat>(0.5f, -0.5f, -0.5f));
    vertices.push_back(Vector3<GLfloat>(-0.5f, -0.5f, -0.5f));
    vertices.push_back(Vector3<GLfloat>(0.5f, 0.5f, -0.5f));
    vertices.push_back(Vector3<GLfloat>(0.5f, -0.5f, 0.5f));
    vertices.push_back(Vector3<GLfloat>(-0.5f, -0.5f, 0.5f));

    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(1); indices.push_back(3); indices.push_back(4);
    indices.push_back(5); indices.push_back(6); indices.push_back(3);
    indices.push_back(7); indices.push_back(3); indices.push_back(6);
    indices.push_back(2); indices.push_back(4); indices.push_back(7);
    indices.push_back(0); indices.push_back(7); indices.push_back(6);
    indices.push_back(0); indices.push_back(5); indices.push_back(1);
    indices.push_back(1); indices.push_back(5); indices.push_back(3);
    indices.push_back(5); indices.push_back(0); indices.push_back(6);
    indices.push_back(7); indices.push_back(4); indices.push_back(3);
    indices.push_back(2); indices.push_back(1); indices.push_back(4);
    indices.push_back(0); indices.push_back(2); indices.push_back(7);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}