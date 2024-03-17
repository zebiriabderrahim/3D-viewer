//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#include "../include/IndexBuffer.h"

namespace v3D {
    IndexBuffer::IndexBuffer(const unsigned int *data, GLuint count): count_(count){
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &rendererID_);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
} // v3D