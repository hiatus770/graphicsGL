#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class VBO
{
    public:
        GLuint ID;
        VBO(GLfloat* vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};

#endif