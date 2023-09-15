#include "scop.hpp"

void ObjParser::toggleSmoothGroup(std::vector<std::string> line, int *smoothingGroup) {
    if (line.size() < 2)
        throw "Incorrect input for smoothing group";
    
    if (line[1] == "off")
        *smoothingGroup = 0;
    else
        *smoothingGroup = std::stoi(line[1]);
}

void ObjParser::addFace(std::vector<std::string> line, int smoothingGroup) {
    if (line.size() < 4)
        throw "Incorrect input for face";

    faces.push_back(Face(std::stoi(line[1]), std::stoi(line[2]), std::stoi(line[3]), smoothingGroup));
}

void ObjParser::addVertice(std::vector<std::string> line) {
    if (line.size() < 4)
        throw "Incorrect input for vertice";
    
    vertices.push_back(Vertice(std::stof(line[1]), std::stof(line[2]), std::stof(line[3])));
}

ObjParser::ObjParser(std::string filePath) {
    std::fstream file(filePath);
    int smoothingGroup = 0;

    for (std::string line; std::getline(file, line);) {
        std::string::size_type commentIndex;
        if ((commentIndex = line.find('#')) != std::string::npos) {
            line.erase(commentIndex);
        }

        if (!line.length())
            continue ;
        std::vector<std::string> tab = split(line, " \n");

        if (tab[0] == "v")
            addVertice(tab);
        else if (tab[0] == "f")
            addFace(tab, smoothingGroup);
        else if (tab[0] == "s")
            toggleSmoothGroup(tab, &smoothingGroup);
    }

    std::cout << vertices.size() << " vertices\n";
    std::cout << faces.size() << " faces\n";
}

ObjParser::~ObjParser() {
    std::cout << "ObjParser destructor" << "\n";
}