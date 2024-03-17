//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#include "../include/VertexBuffer.h"

namespace v3D {
    VertexBuffer::VertexBuffer(const float *data, GLuint size) {
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &rendererID_);
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

} // v3D