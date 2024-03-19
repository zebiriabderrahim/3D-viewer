//
// Created by ABDERRAHIM ZEBIRI on 2024-03-17.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace v3D {
    Texture::Texture(const std::string &path)
        : rendererID_(0), filePath_(path), localBuffer_(nullptr), width_(0), height_(0), BPP_(0){
        stbi_set_flip_vertically_on_load(1);
        localBuffer_ = stbi_load(path.c_str(), &width_, &height_, &BPP_, 4);

        glGenTextures(1, &rendererID_);
        glBindTexture(GL_TEXTURE_2D, rendererID_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer_);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (localBuffer_) {
            stbi_image_free(localBuffer_);
        }

    }

    Texture::~Texture() {
        glDeleteTextures(1, &rendererID_);
    }

    void Texture::bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererID_);
    }

    void Texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

} // v3D