#include "scop.hpp"

const std::string Shader::getType() const {
    if (type == VERTEX_SHADER)
        return "VERTEX SHADER";
    return "FRAGMENT_SHADER";
}

Shader::Shader(const ShaderType type, const std::string &filePath)
: type(type), filePath(filePath)
{
    std::stringstream stream;
    int success = 0;
    char logs[512];
    
    for (size_t i = 0; i < sizeof(logs); i++) logs[i] = 0;

    file.open(filePath);
    stream << file.rdbuf();

    code = stream.str();
    codePointer = code.c_str();


    id = glCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    std::cout << "id : " << id << "\n";
    
    glShaderSource(id, 1, &codePointer, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "mince : " << logs << " avec " << id << "\n";
        glGetShaderInfoLog(id, sizeof(logs), NULL, logs);
        throw std::runtime_error("ERROR: (" + getType() + " COMPILATION) :\n");
    }
}



Shader::~Shader()
{
    glDeleteShader(id);
}