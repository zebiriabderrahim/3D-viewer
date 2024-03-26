//
// Created by ABDERRAHIM ZEBIRI on 2024-03-21.
//

#ifndef INC_3DVIEWERAPP_WINDOW_H
#define INC_3DVIEWERAPP_WINDOW_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace v3D {

    class Window
    {
    public:
        enum Key
        {
            ESC = GLFW_KEY_ESCAPE,
            T = GLFW_KEY_T,
            W = GLFW_KEY_W,
            A = GLFW_KEY_A,
            S = GLFW_KEY_S,
            D = GLFW_KEY_D,
            Q = GLFW_KEY_Q,
            E = GLFW_KEY_E,
            SPACE = GLFW_KEY_SPACE
        };

    public:
        Window();
        ~Window();

        bool init();

        void swap();
        void pollEvent();

        bool getKeyHold(Key k);
        bool getKeyPress(Key k);

        void getMouseMotion(double& x, double& y) const;
        [[nodiscard]]int getMouseScrollDirection() const;

        void showMouse();
        void hideMouse();

        double getTick();

        bool shouldClose() const;
        [[nodiscard]] bool shouldResize() const;

        [[nodiscard]] GLFWwindow* getGLFWWindow() const;
        [[nodiscard]] int getWidth();
        [[nodiscard]] int getHeight();

    private:
        GLFWwindow* window_;

        struct WindowData
        {
            bool shouldClose_;
            bool shouldResize_;
            int width_, height_;
        } windowData_;

        std::unordered_map<Key, bool> keyHolds_;
        std::unordered_map<Key, bool> keyPresses_; // For key press tracking if needed
        double lastMouseX_, lastMouseY_;
        int scrollDirection_;
        double lastTime_;
    };

} // v3D

#endif //INC_3DVIEWERAPP_WINDOW_H
