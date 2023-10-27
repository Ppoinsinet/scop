#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "scop.hpp"

class Texture {
public:
    int height;
    int width;
    int bpp;
    int type;
    std::string filepath;
    unsigned char *data;
    GLuint obj;

    Texture(GLenum type, const std::string &filepath) {
        this->type = type;
        this->filepath = filepath;
    }

    void load() {
        stbi_set_flip_vertically_on_load(1);
        data = stbi_load(filepath.c_str(), &width, &height, &bpp, 0);
        
        if (!data) {
            std::cout << "Could not load texture '" << filepath << "' : " << stbi_failure_reason() << "\n";
            exit(1);
        }

        handleOpenGL();
        std::cout << "Texture was loaded : " << width << "x" << height << "\n";
    }

    void handleOpenGL() {
        glGenTextures(1, &obj);
        glBindTexture(type, obj);

        if (type != GL_TEXTURE_2D) {
            std::cerr << "Texture type not implemented\n";
            exit(1);
        }

        switch (bpp)
        {
        case 1:
            glTexImage2D(type, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        case 2:
            glTexImage2D(type, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
            break;
        case 3:
            glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case 4:
            glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        
        default:
            std::cerr << "Texture bpp not implemented\n";
            exit(1);
        }

        glTexParameterf(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(type, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glBindTexture(type, 0);
        stbi_image_free(data);
    }

    void bind(GLenum textureUnit) {
        glActiveTexture(textureUnit);
        glBindTexture(type, obj);
    }


};

#endif