#include "scop.hpp"

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

    scale += 0.002f;
    return (GLfloat[]){
        cosf(scale), 0.0f,  -sinf(scale), 0.0f,
        0.0f,        1.0f,  0.0f,         0.0f,
        sinf(scale), 0.0f,  cosf(scale),  0.0f,
        0.0f,        0.0f,  0.0f,         1.0f
    };
}

Matrix<4, 4, GLfloat> getProjection(Window<Scene> *win, GLfloat aspectRatio) {

    GLfloat d = 1.0f/((tanf(toRadian(win->data->camera.FOV)/ 2.0f)));

    float A = (-win->data->camera.farZ - win->data->camera.nearZ) / (win->data->camera.nearZ - win->data->camera.farZ);
    float B = (2.0f * win->data->camera.farZ * win->data->camera.nearZ) / (win->data->camera.nearZ - win->data->camera.farZ);

    return (GLfloat[]) {
        d/aspectRatio,    0.0f, 0.0f, 0.0f,
        0.0f,             d,    0.0f, 0.0f,
        0.0f,             0.0f, A,  B,
        0.0f,             0.0f, 1.0f, 0.0f
    };
}

#include "Texture.hpp"
#include "Scene.hpp"

Texture *tex;
GLuint gSamplerLocation;
GLuint gWorldLocation;

void onUpdate(Window<Scene> *win, Scene *data) {
    (void)win;
    (void)data;
    
    glfwGetWindowSize(win->window, &win->width, &win->height);    
    GLfloat aspectRatio = (GLfloat)win->width / (GLfloat)win->height;

    Matrix<4U, 4U, GLfloat> rotation = getRotation();
    Matrix<4U, 4U, GLfloat> projection = getProjection(win, aspectRatio);

    VAO *vao = data->listVAO[data->listVAO.size() - 1];
    // vao->print();

    float minX = vao->vertices[0].x;
    float maxX = minX;

    float minZ = vao->vertices[0].z;
    float maxZ = minZ;

    for (unsigned int i = 1; i < vao->vertices.size(); i++) {
        if (vao->vertices[i].x < minX)
            minX = vao->vertices[i].x;
        if (vao->vertices[i].x > maxX)
            maxX = vao->vertices[i].x;

        if (vao->vertices[i].z < minZ)
            minZ = vao->vertices[i].z;
        if (vao->vertices[i].z > maxZ)
            maxZ = vao->vertices[i].z;
    }

    Matrix<4, 4, GLfloat> translation = (GLfloat[]) {
        1.0f, 0.0f, 0.0f, -(maxX + minX) / 2,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, -(maxZ + minZ) / 2,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    // data->camera.position = Vector3<GLfloat>(position[0], position[1], position[2] - 5.0f);

    // Transformation matrix
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (projection * data->camera.getMatrix() * rotation * translation).data);

    tex->bind(GL_TEXTURE0);
    glUniform1i(gSamplerLocation, 0);

    std::vector<Vector2<GLfloat> > texCoords;
    srand(1);
    for (unsigned int i = 0; i < vao->vertices.size(); i++) {
        texCoords.push_back(Vector2<GLfloat>((float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
    }

    // Bind CBO
    glBindBuffer(GL_ARRAY_BUFFER, vao->CBO);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vector2<GLfloat>), texCoords.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2<GLfloat>), nullptr);
    glEnableVertexAttribArray(1);

    vao->preDraw();

    glDrawElements(GL_TRIANGLES, vao->indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}