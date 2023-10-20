#include <scop.hpp>

class ObjParser {
    public:
        std::vector<Vector3<GLfloat> > vertices;
        std::vector<Face> faces;

        void addVertice(std::vector<std::string> line);
        void addFace(std::vector<std::string> line, int smoothingGroup);
        void toggleSmoothGroup(std::vector<std::string> line, int *smoothingGroup);

        ObjParser(std::string filePath);
        ~ObjParser();
};