cmake_minimum_required(VERSION 3.10)
project(CoreLib)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CORE_SRC
        src/VertexBuffer.cpp
        src/IndexBuffer.cpp
        src/VertexArray.cpp
        src/Shader.cpp
        src/ShaderProgram.cpp
        src/Renderer.cpp
        src/Texture.cpp
        src/Window.cpp
        src/UniformBuffer.cpp
        src/Camera.cpp src/Logger.cpp include/Logger.h)


add_library(Core ${CORE_SRC})
target_include_directories(Core PUBLIC ${CORE_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
target_link_libraries(Core OpenGL::GL)

find_package(GLEW REQUIRED)
target_link_libraries(Core GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Core glm::glm)

