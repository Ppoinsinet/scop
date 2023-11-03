#ifndef VAO_HPP
#define VAO_HPP

#include "scop.hpp"
#include "ObjParser.hpp"

class VAO {
public:
    GLuint gSamplerLocation;
    Texture *tex;
    std::vector<Vector3<GLfloat> > vertices;
    std::vector<unsigned int> indices;
    std::vector<Vector2<GLfloat> > textureCoords;

    Vector3<GLfloat> position;
    float scale;

    unsigned int CBO; // Colors buffer object
    unsigned int VBO; // Vertex buffer object
    unsigned int IBO; // Indices buffer object

    VAO(const std::string &path) {
        scale = 1.0f;
        ObjParser t(path);
        vertices = t.vertices;

        for (size_t i = 0; i < t.faces.size(); i++) {
            for (int k = 0; k < 3; k++) {
                indices.push_back(t.faces[i].verticesIndex[k]);
            }
        }
    }

    VAO(const VAO &ref) {
        gSamplerLocation = ref.gSamplerLocation;
        tex = ref.tex;
        vertices = ref.vertices;
        indices = ref.indices;
        textureCoords = ref.textureCoords;

        CBO = ref.CBO;
        VBO = ref.VBO;
        IBO = ref.IBO;
    }

    VAO(const ObjParser &data) {

        scale = 1.0f;
        vertices = data.vertices;

        for (size_t i = 0; i < data.faces.size(); i++) {
            for (int k = 0; k < 3; k++) {
                indices.push_back(data.faces[i].verticesIndex[k]);
            }
        }
    }

    void print() {
        std::cout << "gSampler : " << gSamplerLocation << "\n";
        std::cout << "tex : " << tex << "\n";
        std::cout << "vertices : " << vertices.size() << "\n";
        std::cout << "indices : " << indices.size() << "\n";
        std::cout << "texCoords : " << textureCoords.size() << "\n";
        std::cout << "CBO : " << CBO << "\n";
        std::cout << "IBO : " << IBO << "\n";
        std::cout << "VBO : " << VBO << "\n";
    }

    VAO &operator=(const VAO &ref) {
        gSamplerLocation = ref.gSamplerLocation;
        tex = ref.tex;
        vertices = ref.vertices;
        indices = ref.indices;
        textureCoords = ref.textureCoords;

        CBO = ref.CBO;
        VBO = ref.VBO;
        IBO = ref.IBO;
        return *this;
    }

    void init() {
        glGenBuffers(1, &CBO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);
    }

    void preDraw() {
        // Bind CBO
        // glBindBuffer(GL_ARRAY_BUFFER, CBO);
        // glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vector2<GLfloat>), texCoords.data(), GL_DYNAMIC_DRAW);
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2<GLfloat>), nullptr);
        // glEnableVertexAttribArray(1);

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3<GLfloat>), vertices.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3<GLfloat>), nullptr);
        glEnableVertexAttribArray(0);

        // Bind IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    ~VAO() {
        glDeleteBuffers(1, &CBO);
        glDeleteBuffers(1, &VBO);
    }

    void getTextureCoords() {
        std::vector<Vector2<GLfloat> > tmp;
        srand(1);
        for (unsigned int i = 0; i < vertices.size(); i++) {
            tmp.push_back(Vector2<GLfloat>((float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
        }
        textureCoords = tmp;
    }
};

#endif