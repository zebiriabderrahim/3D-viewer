cmake_minimum_required(VERSION 3.10)
project(zyxDiveApp)

# Set the include directories for the app module
set(APP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(APP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(${PROJECT_NAME} ${APP_SRC_DIR}/main.cpp include/Event.h include/MouseEvent.h include/KeyEvent.h)

include_directories(${APP_INCLUDE_DIR})

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

target_link_libraries(${PROJECT_NAME} Core)
