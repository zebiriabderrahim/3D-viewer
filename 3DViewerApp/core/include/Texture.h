//
// Created by ABDERRAHIM ZEBIRI on 2024-03-17.
//

#ifndef INC_3DVIEWERAPP_TEXTURE_H
#define INC_3DVIEWERAPP_TEXTURE_H

#include <GL/glew.h>
#include <string>
#include "Renderer.h"

namespace v3D {

    class Texture {

    public:
        Texture(const std::string& path);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        [[nodiscard]] inline int getWidth() const { return width_; }
        [[nodiscard]] inline int getHeight() const { return height_; }

    private:
        GLuint rendererID_;
        std::string filePath_;
        unsigned char* localBuffer_;
        int width_, height_, BPP_;

    };

} // v3D

#endif //INC_3DVIEWERAPP_TEXTURE_H
