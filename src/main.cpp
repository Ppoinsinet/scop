#include "scop.hpp"

#define WINDOW_HEIGHT 150
#define WINDOW_WIDTH 150

#include <math.h>

Vector3<GLfloat> position(0.0, 0.0, 3.5);

void drawObjFaces(ObjParser *data) {
    std::vector<Vertice> vertices;

    for (size_t i = 0; i < data->faces.size(); i++) {
        for (int j = 0; j < 3; j++) {
            vertices.push_back(data->vertices[data->faces[i].verticesIndex[j]]);
            // std::cout << "x = " << data->vertices[data->faces[i].verticesIndex[j]].x << " y = " << data->vertices[data->faces[i].verticesIndex[j]].y << " z = " << data->vertices[data->faces[i].verticesIndex[j]].z << "\n";
        }
    }

    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Position VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

    glBindVertexArray(0);
}

void onUpdate(Window<ObjParser *> *win, ObjParser *data) {
    (void)win;
    (void)data;

    float verticalFOV = 90;

    std::vector<Vertice> vertices(data->vertices);

    for (size_t i = 0; i < 6; i++) {
        vertices[i].x += position.x;
        vertices[i].y += position.y;
        vertices[i].z += position.z;
    }

    for (size_t i = 0; i < 6; i++) {
        vertices[i].x = vertices[i].x / (vertices[i].z * tan(verticalFOV / 2));
        vertices[i].y = vertices[i].y / (vertices[i].z * tan(verticalFOV / 2));
        vertices[i].z = 0;
    }

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    // Position VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertice) , vertices.data(), GL_STATIC_DRAW);
    
    unsigned int IBO = 0;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < data->faces.size(); i++)
        for (int j = 0; j < 3; j++) {
            indices.push_back(static_cast<unsigned int>(data->faces[i].verticesIndex[j]));
        }

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // draw
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawElements(GL_TRIANGLES, vertices.size() * 3, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}

void onPress(Window<ObjParser *> *win, ObjParser *data) {
    (void)win;
    (void)data;
    position.z -= 0.2;
    position.x += 0.2;
    std::cout << "press\n";
}

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Incorrect input\n";
        exit(1);
    }
    ObjParser parser(av[1]);

    Window<ObjParser *> window;

    try
    {
        // useShaders(&window);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);

        window.data = &parser;
        window.keyHandle[GLFW_KEY_Q] = onPress;
        window.create();
        window.updateFunction = onUpdate;

        window.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}