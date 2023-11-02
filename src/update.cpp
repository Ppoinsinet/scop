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

template<typename T>
Matrix<4, 4, GLfloat> getProjection(Window<T*> *win, GLfloat aspectRatio) {

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

#include "Texture.hpp"

Texture *tex;
GLuint gSamplerLocation;
GLuint gWorldLocation;

void onUpdate(Window<VAO *> *win, VAO *data) {
    (void)win;
    (void)data;
    
    glfwGetWindowSize(win->window, &win->width, &win->height);    
    GLfloat aspectRatio = (GLfloat)win->width / (GLfloat)win->height;

    Matrix<4U, 4U, GLfloat> rotation = getRotation();
    Matrix<4U, 4U, GLfloat> projection = getProjection(win, aspectRatio);

    float minX = data->vertices[0].x;
    float maxX = minX;

    float minZ = data->vertices[0].z;
    float maxZ = minZ;

    for (unsigned int i = 1; i < data->vertices.size(); i++) {
        if (data->vertices[i].x < minX)
            minX = data->vertices[i].x;
        if (data->vertices[i].x > maxX)
            maxX = data->vertices[i].x;

        if (data->vertices[i].z < minZ)
            minZ = data->vertices[i].z;
        if (data->vertices[i].z > maxZ)
            maxZ = data->vertices[i].z;
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
    for (unsigned int i = 0; i < data->vertices.size(); i++) {
        texCoords.push_back(Vector2<GLfloat>((float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
    }

    // Bind CBO
    glBindBuffer(GL_ARRAY_BUFFER, data->CBO);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vector2<GLfloat>), texCoords.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2<GLfloat>), nullptr);
    glEnableVertexAttribArray(1);

    data->preDraw();

    glDrawElements(GL_TRIANGLES, data->indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}