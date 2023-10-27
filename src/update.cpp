#include "scop.hpp"

extern Matrix<4, 1, GLfloat> position;

void *getOffset(char *addr, int offset) {
    void *r = &addr[offset];
    // float *f = (float*)r;
    // std::cout << "float : " << std::dec << *f << "\n";
    return r;
}

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

Matrix<4, 4, GLfloat> getProjection(Window<ObjParser*> *win, GLfloat aspectRatio) {

    GLfloat d = 1.0f/((tanf(toRadian(win->camera.FOV)/ 2.0f)));

    float A = (-win->camera.farZ - win->camera.nearZ) / (win->camera.nearZ - win->camera.farZ);
    float B = (2.0f * win->camera.farZ * win->camera.nearZ) / (win->camera.nearZ - win->camera.farZ);

    return (GLfloat[]) {
        d/aspectRatio,    0.0f, 0.0f, 0.0f,
        0.0f,             d,    0.0f, 0.0f,
        0.0f,             0.0f, A,  B,
        0.0f,             0.0f, 1.0f, 0.0f
    };
}

extern std::vector<Vector3<GLfloat> > vertices;
extern std::vector<unsigned int> indices;

#include "Texture.hpp"

Texture *tex;
GLuint gSamplerLocation;

void onUpdate(Window<ObjParser *> *win, ObjParser *data) {
    (void)win;
    (void)data;
    

    glfwGetWindowSize(win->window, &win->width, &win->height);    
    GLfloat aspectRatio = (GLfloat)win->width / (GLfloat)win->height;

    Matrix<4U, 4U, GLfloat> rotation = getRotation();
    Matrix<4U, 4U, GLfloat> projection = getProjection(win, aspectRatio);

    float minX = vertices[0].x;
    float maxX = minX;

    float minZ = vertices[0].z;
    float maxZ = minZ;

    for (unsigned int i  = 1; i < vertices.size(); i++) {
        if (vertices[i].x < minX)
            minX = vertices[i].x;
        if (vertices[i].x > maxX)
            maxX = vertices[i].x;

        if (vertices[i].z < minZ)
            minZ = vertices[i].z;
        if (vertices[i].z > maxZ)
            maxZ = vertices[i].z;
    }

    Matrix<4, 4, GLfloat> translation = (GLfloat[]) {
        1.0f, 0.0f, 0.0f, -(maxX + minX) / 2,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, -(maxZ + minZ) / 2,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    win->camera.position = Vector3<GLfloat>(position[0], position[1], position[2] - 5.0f);

    // Transformation matrix
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (projection * win->camera.getMatrix() * rotation * translation).data);

    tex->bind(GL_TEXTURE0);
    glUniform1i(gSamplerLocation, 0);


    std::vector<Vector2<GLfloat> > texCoords;
    srand(1);
    for (unsigned int i = 0; i < vertices.size(); i++) {
        texCoords.push_back(Vector2<GLfloat>((float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
        // std::cout << "test : \n" << texCoords[texCoords.size() - 1];
    }
    
    unsigned int CBO = 0;
    glGenBuffers(1, &CBO);

    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vector2<GLfloat>), texCoords.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2<GLfloat>), nullptr);
    glEnableVertexAttribArray(1);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    // Position VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3<GLfloat>), vertices.data(), GL_DYNAMIC_DRAW);

    // draw
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3<GLfloat>), nullptr);
    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &VBO);

    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &CBO);
}