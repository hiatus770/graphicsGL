#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// Outputs the color of the vertex to the fragment shader
out vec3 color; 
// Outputs the texture coordinates of the vertex to the fragment shader
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 camMatrix; 

void main()
{
    // gl_Position = camMatrix * vec4(aPos, 1.0f);
    gl_Position = camMatrix * model * vec4(aPos, 1.0f);
    color = aColor;
    TexCoord = aTex;
}