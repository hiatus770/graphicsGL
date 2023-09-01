#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <cerrno> 

std::string get_file_contents(const std::string filename);

class Shader
{
    public: 
        GLuint ID;
        Shader(const std::string vertexFile, const std::string fragmentFile);

        void Activate(); 
        void Delete(); 
}; 

#endif