//
// Created by ABDERRAHIM ZEBIRI on 2024-03-21.
//

#include "Window.h"
#include <iostream>
#include "Logger.h"


namespace v3D {

    Window::Window(): window_(nullptr)
    {
        windowData_.width_ = 800;
        windowData_.height_ = 600;
        windowData_.shouldClose_ = false;
        windowData_.shouldResize_ = false;
        lastMouseX_ = 0.0;
        lastMouseY_ = 0.0;
        scrollDirection_ = 0;
    }

    Window::~Window()
    {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

    bool Window::init()
    {
        if (!glfwInit())
        {
            LOG_ERROR("Failed to initialize GLFW");
            return false;
        }
        LOG_INFO("GLFW initialized");

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif

        window_ = glfwCreateWindow(windowData_.width_,
                                   windowData_.height_,
                                   "OpenGL Window",
                                   nullptr,
                                   nullptr);
        if (!window_)
        {
            LOG_ERROR("GLFW window creation failed");
            glfwTerminate();
            return false;
        }
        LOG_INFO("GLFW window created");



        glfwMakeContextCurrent(window_);
  //      glfwSetWindowUserPointer(window_, this);
        // Set GLFW callbacks here (for key, mouse movement, mouse button, scroll, etc.)
//        glfwSetKeyCallback(window_, [](GLFWwindow* window, Key key, int scancode, int action, int mods){
//            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            if (action == GLFW_PRESS)
//            {
//                win->keyHolds_[key] = true;
//                win->keyPresses_[key] = true; // If tracking press events separately
//            }
//            else if (action == GLFW_RELEASE)
//            {
//                win->keyHolds_[key] = false;
//                win->keyPresses_[key] = false; // Reset press state if needed
//            }
//        });

//        // Mouse movement callback
//        glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos){
//            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            win->lastMouseX_ = xpos;
//            win->lastMouseY_ = ypos;
//        });
//
//        // Mouse scroll callback
//        glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset){
//            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            win->scrollDirection_ = (yoffset > 0) ? 1 : (yoffset < 0) ? -1 : 0;
//        });

        return true;
    }

    void Window::swap()
    {
        glfwSwapBuffers(window_);
    }

    void Window::pollEvent()
    {
        windowData_.shouldClose_ = glfwWindowShouldClose(window_);
        windowData_.shouldResize_ = false; // Reset after checking
        glfwPollEvents();
    }

    bool Window::getKeyHold(Key k)
    {
        return keyHolds_[k];
    }

    bool Window::getKeyPress(Key k)
    {
        bool pressed = keyPresses_[k];
        keyPresses_[k] = false; // Reset after checking
        return pressed;
    }

    void Window::getMouseMotion(double& x, double& y) const
    {
        x = lastMouseX_;
        y = lastMouseY_;
    }

    int Window::getMouseScrollDirection() const
    {
        return scrollDirection_;
    }

    void Window::showMouse()
    {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::hideMouse()
    {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    double Window::getTick()
    {
        return glfwGetTime();
    }

    bool Window::shouldClose() const
    {
        return windowData_.shouldClose_;
    }

    bool Window::shouldResize() const
    {
        // Implement resize checking logic if needed
        // This flag must be manually managed in a window size callback
        return windowData_.shouldResize_;
    }

    int Window::getWidth()
    {
        glfwGetWindowSize(window_, &windowData_.width_, nullptr);
        return windowData_.width_;
    }

    int Window::getHeight()
    {
        glfwGetWindowSize(window_, nullptr, &windowData_.height_);
        return windowData_.height_;
    }

    GLFWwindow *Window::getGLFWWindow() const {
        return window_;
    }

} // v3D