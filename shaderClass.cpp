#include "shaderClass.h"

std::string get_file_contents(const std::string filename){
    std::ifstream in(filename, std::ios::in | std::ios::binary); 
    if (in){
        std::string contents; 
        in.seekg(0, std::ios::end); 
        contents.resize(in.tellg()); 
        in.seekg(0, std::ios::beg); 
        in.read(&contents[0], contents.size()); 
        in.close(); 
        return(contents); 
    }
    throw(errno); 
}

Shader::Shader (const std::string vertexFile, const std::string fragmentFile){
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    // Compile shaders
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    ID = glCreateProgram();

    // Attach shaders to the program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    // Link the program
    glLinkProgram(ID);

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}