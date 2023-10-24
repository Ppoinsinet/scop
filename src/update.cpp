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

    GLfloat FOV = 45.0f;
    GLfloat d = 1.0f/((tanf(toRadian(FOV)/ 2.0f)));

    float nearZ = 1.0f;
    float farZ = 12.0f;

    float A = (-farZ - nearZ) / (nearZ - farZ);
    float B = (2.0f * farZ * nearZ) / (nearZ - farZ);

    return (GLfloat[]) {
        d/aspectRatio,    0.0f, 0.0f, 0.0f,
        0.0f,             d,    0.0f, 0.0f,
        0.0f,             0.0f, A, B,
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
    
    glfwGetWindowSize(win->window, &win->width, &win->height);
    GLfloat aspectRatio = (GLfloat)win->width / (GLfloat)win->height;

    // std::cout << "vertmices : " << vertices.size() << " et indices : " << indices.size() << "\n";

    Matrix<4U, 4U, GLfloat> rotation = getRotation();
    Matrix<4U, 4U, GLfloat> projection = getProjection(aspectRatio);

    Matrix<4, 4, GLfloat> translation = (GLfloat[]) {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 10.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    Matrix<4, 4, GLfloat> transformationMatrix = projection * translation * rotation;    
    (void)transformationMatrix;
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, transformationMatrix.data);

    std::vector<Vector3<GLfloat> > colors;
    srand(1);
    for (unsigned int i = 0; i < vertices.size(); i++)
        colors.push_back(Vector3<GLfloat>(((GLfloat)rand()) / RAND_MAX , ((GLfloat)rand()) / RAND_MAX, ((GLfloat)rand()) / RAND_MAX));
    unsigned int CBO = 0;
    glGenBuffers(1, &CBO);

    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(Vector3<GLfloat>), colors.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);


    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    // Position VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3<GLfloat>), vertices.data(), GL_DYNAMIC_DRAW);

    // draw
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &VBO);

    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &CBO);
}