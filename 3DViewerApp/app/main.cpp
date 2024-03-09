#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include "spdlog/spdlog.h"

#include <string>
#include <sstream>
#include <fstream>

#define PBYTE(CHAINE) ( (CHAINE) != NULL ? (CHAINE) : (const GLubyte *) "????" )


static GLuint compileShader(GLuint type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
static GLuint creatShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int progId = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(progId, vs);
    glAttachShader(progId, fs);
    glLinkProgram(progId);
    glValidateProgram(progId);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return progId;
}

std::string readShader(const std::string& filepath){
    std::ifstream stream(filepath);
    //error handling
    if(!stream){
        std::cerr << "Failed to open file" << std::endl;
    }
    std::string line;
    std::stringstream ss;
    while(getline(stream, line)){
        ss << line << '\n';
    }
    return ss.str();
}



int main()
{

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "3D Viewer", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }



    const GLubyte *glVersion  = glGetString( GL_VERSION );
    const GLubyte *glVendor   = glGetString( GL_VENDOR );
    const GLubyte *glRenderer = glGetString( GL_RENDERER );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    std::cout << "// OpenGL " << PBYTE(glVersion) << PBYTE(glVendor) << std::endl;
    std::cout << "// GPU    " << PBYTE(glRenderer) << std::endl;
    std::cout << "// GLSL   " << PBYTE(glslVersion) << std::endl;

    float positions[] = {
        -1.0f, -0.5f,
         0.0f,  0.5f,
         1.0f, 0.5f
    };
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);


//    std::string vertexShader = readShader("../vertexShader.glsl");
//    std::string fragmentShader = readShader("../fragmentShader.glsl");
//    unsigned int shader = creatShader(vertexShader, fragmentShader);
//    glUseProgram(shader);




    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");
    spdlog::info("This message should be displayed..");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    glfwTerminate();
    return 0;
}

