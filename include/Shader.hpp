#ifndef SHADER_HPP
#define SHADER_HPP

#include "scop.hpp"

typedef enum e_ShaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER

} ShaderType;

class Shader
{
private:
    const ShaderType type;
    const std::string filePath;

    std::string code;
    const char *codePointer;
    std::ifstream file;
    int id;
    
public:
    Shader(const ShaderType type, const std::string &filePath);
    ~Shader();

    int getId() {return id;}

    const std::string getType() const;
};



#endif