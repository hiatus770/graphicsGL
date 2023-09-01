#include "Texture.h" 

/**
 * @brief Construct a new Texture:: Texture object
*/
Texture::Texture(const char *imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType){
    type = texType;
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);

    // Generate the texture
    glGenTextures(1, &ID);
    // Bind the texture
    glActiveTexture(slot);
    // Bind the texture to the currently bound texture object
    glBindTexture(texType , ID);

    // Configure the type of algorithm to make it bigger or smaller 
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR

    // COnfigure the repearint
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_CLAMP_TO_EDGE
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_CLAMP_TO_EDGE

    // Asisgns to image to the OPENgl texture obejct 
    unsigned char *bytes = stbi_load(imagePath, &widthImg, &heightImg, &numColCh, 0);

    // Generate the texture
    glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generate the mipmap
    glGenerateMipmap(texType);

    // Free the image memory
    stbi_image_free(bytes); 

    // Unbind the texture
    glBindTexture(texType, 0);


}

/**
 * @brief Assigns the texture to a shader
 * 
 * @param shader 
 * @param uniform 
 * @param unit 
*/
void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit){
    // Get the uniform variable location
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Activate the shader
    shader.Activate();
    // Assign the texture unit to the shader uniform
    glUniform1i(texUni, unit);
}

/**
 * @brief Binds the texture
 * 
*/
void Texture::Bind(){
    glBindTexture(type, ID);
}

/**
 * @brief Unbinds the texture
 * 
*/
void Texture::Unbind(){
    glBindTexture(type, 0);
}

/**
 * @brief Deletes the texture
 * 
*/
void Texture::Delete(){
    glDeleteTextures(1, &ID);
}
