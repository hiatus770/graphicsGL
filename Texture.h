#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb/stb_image.h" 
#include <iostream>
#include "shaderClass.h"

class Texture
{
public:
    Texture(const char *imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    
    void texUnit(Shader &shader, const char *uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();

    GLuint ID;
    GLenum type;  
};

#endif