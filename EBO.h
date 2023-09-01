#ifndef EBO_CLASS_H 
#define EBO_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class EBO
{
    public:
        GLuint ID;
        EBO(GLuint* indices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};

#endif
