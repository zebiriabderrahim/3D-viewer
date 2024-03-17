cmake_minimum_required(VERSION 3.10)
project(3DViewerAppExecutable)

# Set the include directories for the app module

add_executable(3DViewerApp src/main.cpp)

include_directories(${APP_INCLUDE_DIR})

find_package(glfw3 REQUIRED)
target_link_libraries(3DViewerApp glfw)

find_package(GLEW REQUIRED)
target_link_libraries(3DViewerApp GLEW::GLEW)

find_package(spdlog REQUIRED)
target_link_libraries(3DViewerApp spdlog::spdlog)

target_link_libraries(3DViewerApp Core)
