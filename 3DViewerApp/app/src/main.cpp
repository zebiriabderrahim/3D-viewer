#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"


#define PBYTE(CHAINE) ((CHAINE) != NULL ? (reinterpret_cast<const char*>(CHAINE)) : "????")


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        spdlog::info("Space key is pressed");
    }
}


int main() {
    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif


    GLFWwindow *window = glfwCreateWindow(640, 480, "3D Viewer", nullptr, nullptr);
    if (!window) {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        spdlog::error("Failed to initialize GLEW");
        return -1;
    }

    // Output OpenGL, GPU, and GLSL versions
    spdlog::info("OpenGL {}", PBYTE(glGetString(GL_VERSION)), PBYTE(glGetString(GL_VENDOR)));
    spdlog::info("Vendor  {}", PBYTE(glGetString(GL_VENDOR)));
    spdlog::info("Renderer  {}", PBYTE(glGetString(GL_RENDERER)));
    spdlog::info("GLSL  {}", PBYTE(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    {

        // Vertex Buffer
        float positions[] = {
                -0.5f, -0.5f,0.0f, 0.0f,
                0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f ,0.0f, 1.0f
        };
        unsigned int indices[] = {
                0, 1, 2, 2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        v3D::VertexArray va;
        v3D::VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        v3D::VertexBufferLayout layout;

        layout.addElement<float>(2);
        layout.addElement<float>(2);
        va.addBuffer(vb, layout);

        v3D::IndexBuffer ib(indices, 6);

        v3D::ShaderProgram shaderProgram;
        shaderProgram.initFromFiles("../../resources/shaders/vertexShader.glsl",
                                    "../../resources/shaders/fragmentShader.glsl");
        shaderProgram.use();
        //shaderProgram.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        v3D::Texture texture("../../resources/textures/wood_texture.png");
        texture.bind();
        shaderProgram.setUniform1i("u_Texture", 0);

        va.unbind();
        vb.unbind();
        ib.unbind();
        shaderProgram.unuse();


        glClearColor(0.55f, 0.5f, 0.5f, 1.0f);

        v3D::Renderer renderer;


        // Main loop
        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            renderer.clear();
            renderer.draw(va, ib, shaderProgram);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        // Cleanup
        texture.unbind();
        spdlog::info("Closing application");
    }
    glfwTerminate();
    return 0;
}
