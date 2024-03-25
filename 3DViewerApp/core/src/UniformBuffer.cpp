//
// Created by ABDERRAHIM ZEBIRI on 2024-03-24.
//

#include "UniformBuffer.h"

namespace v3D {

    UniformBuffer::UniformBuffer(const void *data, GLuint size) {
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_UNIFORM_BUFFER, rendererID_);
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
    }

    UniformBuffer::~UniformBuffer() {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glDeleteBuffers(1, &rendererID_);
    }

    void UniformBuffer::bindWithIndex(GLuint index) const {
        glBindBufferBase(GL_UNIFORM_BUFFER, index, rendererID_);
    }

    void UniformBuffer::setData(const void *data, GLuint size) const {
        glBindBuffer(GL_UNIFORM_BUFFER, rendererID_);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
    }

    void UniformBuffer::bind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, rendererID_);
    }

} // v3D