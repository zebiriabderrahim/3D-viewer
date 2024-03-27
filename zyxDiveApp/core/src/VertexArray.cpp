//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#include "VertexArray.h"

namespace zyxDive {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &rendererID_);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &rendererID_);
    }

    void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const {
        bind();
        vb.bind();
        const auto& elements = layout.getElements();
        unsigned int offset = 0;
        const auto stride = layout.getStride();

        for (unsigned int i = 0; i < elements.size(); ++i) {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type, element.isNormalized, stride,
                                  reinterpret_cast<const void*>(offset));
            offset += element.count * VertexBufferElement::getSizeOfType(element.type);
        }
    }

    void VertexArray::bind() const {
        glBindVertexArray(rendererID_);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }
} // zyxDive