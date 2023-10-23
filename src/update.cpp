#include "scop.hpp"

extern Matrix<4, 1, GLfloat> position;

GLfloat toRadian(GLfloat deg) {
    return (deg * M_PI/180);
}

Matrix<4, 4, GLfloat> getRotation() {
    static float scale = 0.2f;

    scale += 0.02f;
    return (GLfloat[]){
        cosf(scale), 0.0f,  -sinf(scale), 0.0f,
        0.0f,        1.0f,  0.0f,         0.0f,
        sinf(scale), 0.0f,  cosf(scale),  0.0f,
        0.0f,        0.0f,  0.0f,         1.0f
    };
}

Matrix<4, 4, GLfloat> getProjection(GLfloat aspectRatio) {

    GLfloat FOV = 90.0f;
    GLfloat d = 1.0f/((tanf(toRadian(FOV)/ 2.0f)));

    return (GLfloat[]) {
        d/aspectRatio,    0.0f, 0.0f, 0.0f,
        0.0f,             d,    0.0f, 0.0f,
        0.0f,             0.0f, 1.0f, 0.0f,
        0.0f,             0.0f, 1.0f, 0.0f
    };
}

extern std::vector<Vector3<GLfloat> > vertices;
extern std::vector<unsigned int> indices;

Matrix<4, 1, GLfloat> normalize(const Matrix<4, 1, GLfloat> &a) {
    GLfloat norme = sqrt(powf(a.data[0], 2) + powf(a.data[1], 2) + powf(a.data[2], 2) + powf(a.data[3], 2));

    Matrix<4, 1, GLfloat> r(a);
    r.data[0] /= norme;
    r.data[1] /= norme;
    r.data[2] /= norme;
    r.data[3] /= norme;
    return r;
}

void onUpdate(Window<ObjParser *> *win, ObjParser *data) {
    (void)win;
    (void)data;
    
    GLfloat aspectRatio = (GLfloat)win->width / (GLfloat)win->height;

    // std::cout << "vertices : " << vertices.size() << " et indices : " << indices.size() << "\n";

    Matrix<4U, 4U, GLfloat> rotation = getRotation();
    Matrix<4U, 4U, GLfloat> projection = getProjection(aspectRatio);
    

    Matrix<4, 4, GLfloat> translation = (GLfloat[]) {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 5.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    std::vector<Matrix<4, 1, GLfloat> > result;

    for (size_t i = 0; i < vertices.size(); i++) {

        Matrix<4, 1, GLfloat> k;
        k.data[0] = vertices[i].data[0];
        k.data[1] = vertices[i].data[1];
        k.data[2] = vertices[i].data[2];
        k.data[3] = 1.0f;

        Matrix<4, 1, GLfloat> tmp = normalize((projection * translation * rotation) * k);
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