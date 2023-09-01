#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include <iostream>
#include "stb/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

#define homeDir std::string("/home/hiatus/Documents/graphicsGL/") 
#define imageDirectory homeDir + std::string("Textures/") 
#define shaderDirectory homeDir + std::string("Shaders/")


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

#include "pointData.h"


int main()
{
    // Initialize GLFW
    glfwInit();
    

    // Set the version of OpenGL to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Main", NULL, NULL);


    // Check if the window was created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();

        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // This loads all the OpenGL function pointers
    gladLoadGL();

    glfwMakeContextCurrent( window );
    glfwSwapInterval( 0 );

    // Tell OpenGL the size of the rendering window
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Create the shader program
    
    Shader shaderProgram((shaderDirectory + std::string("default.vert")), (shaderDirectory + std::string("default.frag")));

    // Create Vertex Array Object
    VAO VAO1;
    // Bind the VAO so OpenGL knows to use it
    VAO1.Bind();

    // Create a VBO with the specified vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Create a EBO with the specified vertices
    EBO EBO1(indices, sizeof(indices));

    // Position. location 0 in shader
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0);
    // Color. location 1 in shader
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float)));
    // Texture. location 2 in shader
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    Texture amog("/home/hiatus/Documents/graphicsGL/Textures/sus.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    amog.texUnit(shaderProgram, "tex0", 0);
    amog.Bind();

    // Enable the depth 
    glEnable(GL_DEPTH_TEST);

    // Create camera object
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));

    float dt = 0; 

    // Handle timing 
    float frameRate = 600; 
    float lastFrame = 0;
    float currentFrame = glfwGetTime();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    // Create model matrix
    glm::mat4 model = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Handle timing
        currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;

        // Continue if timing is off
        if (dt < 1.0 / frameRate){
            continue;
        }

        // Print the frames per second to the console
        std::cout << 1.0 / dt << std::endl;

        // Update the lstFrame
        lastFrame = currentFrame;
        
        // Specify the color of the background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        // Rotate the model like a clock
        model = glm::rotate(model, glm::radians(20.0f * dt * 0), glm::vec3(fabs(sin(glfwGetTime())), fabs(cos(glfwGetTime())), pow(sin(glfwGetTime()), 2)));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        // Update the Camera 
		camera.Inputs(window); 
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Bind the texture so OpenGL knows which texture we're talking about
        amog.Bind();

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
    
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();


    }

    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}