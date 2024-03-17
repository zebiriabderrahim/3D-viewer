//
// Created by ABDERRAHIM ZEBIRI on 2024-03-17.
//

#include "../include/Renderer.h"
#include "../include/VertexArray.h"
#include "../include/IndexBuffer.h"
#include "../include/ShaderProgram.h"

namespace v3D {

    void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const {
        va.bind();
        ib.bind();
        shader.use();
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::clear() const {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
