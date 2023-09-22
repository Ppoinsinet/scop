#include "scop.hpp"

extern Matrix<4, 1, GLfloat> position;

double toRadian(double deg) {
    return (deg * M_PI/180);
}

Matrix<4, 4, GLfloat> getRotation() {
    static float scale = 0.2f;

    scale += 0.02f;
    return (GLfloat[]){
        cosf(scale), 0.0f, -sinf(scale), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sinf(scale), 0.0f, cosf(scale), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

Matrix<4, 4, GLfloat> getProjection() {

    double FOV = 90.0f;
    GLfloat d = 1.0f/((tanf(toRadian(FOV)/ 2.0f)));

    return (GLfloat[]) {
        d, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

extern std::vector<Vector3<GLfloat>> vertices;
extern std::vector<unsigned int> indices;

void onUpdate(Window<ObjParser *> *win, ObjParser *data) {
    (void)win;
    (void)data;

    std::cout << "vertices : " << vertices.size() << " et indices : " << indices.size() << "\n";

    auto rotation = getRotation();
    auto projection = getProjection();

    Matrix<4, 4, GLfloat> translation = (GLfloat[]) {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.20f, 1.0f
    };
    
    std::vector<Matrix<4, 1, GLfloat>> result;

    for (size_t i = 0; i < vertices.size(); i++) {

        Matrix<4, 1, GLfloat> k;
        k.data[0] = vertices[i].data[0];
        k.data[1] = vertices[i].data[1];
        k.data[2] = vertices[i].data[2];
        k.data[3] = 1.0f;

        Matrix<4, 1, GLfloat> tmp = (projection * translation * rotation) * (k + position);
        result.push_back(tmp);
    }

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    // Position VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, result.size() * sizeof(Matrix<4, 1, GLfloat>), result.data(), GL_DYNAMIC_DRAW);

    // draw
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &VBO);
}