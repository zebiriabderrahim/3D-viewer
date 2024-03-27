#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Window.h"
#include "Logger.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"




#define PBYTE(CHAINE) ((CHAINE) != NULL ? (reinterpret_cast<const char*>(CHAINE)) : "????")

void printGLInfo() {
    LOG_INFO("OpenGL {}", PBYTE(glGetString(GL_VERSION)), PBYTE(glGetString(GL_VENDOR)));
    LOG_INFO("Vendor  {}", PBYTE(glGetString(GL_VENDOR)));
    LOG_INFO("Renderer  {}", PBYTE(glGetString(GL_RENDERER)));
    LOG_INFO("GLSL  {}", PBYTE(glGetString(GL_SHADING_LANGUAGE_VERSION)));;
}
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        LOG_INFO("Space key is pressed");
    }
}


ImGuiIO initImGui(GLFWwindow* glfwWindow) {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL( glfwWindow,true);
    ImGui_ImplOpenGL3_Init("#version 410");
//    bool show_demo_window = true;
//    bool show_another_window = false;
    return io;
}

int main() {
    zyxDive::Window window;
    if (!window.init()) {
        LOG_ERROR("Failed to initialize window");
        return -1;
    }


    if (glewInit() != GLEW_OK) {
        LOG_ERROR("Failed to initialize GLEW");
        return -1;
    }
    GLFWwindow * glfwWindow = window.getGLFWWindow();
    // Setup Dear ImGui context
    ImGuiIO io = initImGui( glfwWindow );



    // Output OpenGL, GPU, and GLSL versions
    printGLInfo();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      {

        // Vertex Buffer
        float positions[] = {
              -50.0f, -50.0f, 0.0f, 0.0f,
              50.0f, -50.0f, 1.0f, 0.0f,
              50.0f, 50.0f, 1.0f, 1.0f,
             -50.0f,50.0f, 0.0f, 1.0f
        };
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        glm::vec3 translationA(200.0f, 200.0f, 0.0f);
        glm::vec3 translationB(400.0f, 200.0f, 0.0f);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));


        zyxDive::VertexArray va;
        zyxDive::VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        zyxDive::VertexBufferLayout layout;

        layout.addElement<float>(2);
        layout.addElement<float>(2);
        va.addBuffer(vb, layout);

        zyxDive::IndexBuffer ib(indices, 6);

        zyxDive::ShaderProgram shaderProgram;
        shaderProgram.initFromFiles("zyxDi/resources/shaders/vertexShader.glsl",
                                    "zyxresources/shaders/fragmentShader.glsl");
        shaderProgram.use();
        //.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


        zyxDive::Texture texture("zyxDiveApp/resources/textures/wood_texture.png");
        texture.bind();

        va.unbind();
        vb.unbind();
        ib.unbind();
        shaderProgram.unuse();


        glClearColor(0.55f, 0.5f, 0.5f, 1.0f);

        zyxDive::Renderer renderer;


        // Main loop
        while (!window.shouldClose()){
            processInput(window.getGLFWWindow());
            renderer.clear();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shaderProgram.use();
                shaderProgram.setUniformMatrix4fv("u_MVP", mvp);
                renderer.draw(va, ib, shaderProgram);
            }
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shaderProgram.use();
                shaderProgram.setUniformMatrix4fv("u_MVP", mvp);
                renderer.draw(va, ib, shaderProgram);
            }

            shaderProgram.setUniform1i("u_Texture", 0);
            window.pollEvent();


            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {

                ImGui::SliderFloat3("translationB", &translationB.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("translationA", &translationA.x, 0.0f, 960.0f);
//
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            window.swap();

        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Cleanup
        texture.unbind();
        LOG_INFO("Closing application");
    }
    return 0;
}
