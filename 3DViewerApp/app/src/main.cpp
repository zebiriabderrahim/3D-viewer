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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../include/imgui.h"
#include "../include/imgui_impl_glfw.h"
#include "../include/imgui_impl_opengl3.h"


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
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
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

        glm::vec3 translation(200.0f, 200.0f, 0.0f);
        glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
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
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;

            shaderProgram.use();
            shaderProgram.setUniform1i("u_Texture", 0);
            shaderProgram.setUniformMatrix4fv("u_MVP", mvp);
            {
                static float f = 0.0f;
                static int counter = 0;

//                ImGui::Begin("Hello, world!");
//                ImGui::Text("This is some useful text.");
//                ImGui::Checkbox("Demo Window", &show_demo_window);
//                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("translation x", &translation.x, 0.0f, 800.0f);
                ImGui::ColorEdit3("clear color", (float*)&clear_color);

//                if (ImGui::Button("Button"))
//                    counter++;
//                ImGui::SameLine();
//                ImGui::Text("counter = %d", counter);
//
//                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);

        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Cleanup
        texture.unbind();
        spdlog::info("Closing application");
    }
    glfwTerminate();
    return 0;
}
