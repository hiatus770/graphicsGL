cmake_minimum_required(VERSION 3.15)

project(GraphicsStuff)
# Add executable target
add_executable(${PROJECT_NAME} 
    main.cpp 
    glad.c 
    shaderClass.cpp 
    VAO.cpp 
    VBO.cpp 
    EBO.cpp 
    Texture.cpp 
    Camera.cpp 
    ./stb/stb.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    dl 
    glfw 
)