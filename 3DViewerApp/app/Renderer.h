//
// Created by ABDERRAHIM ZEBIRI on 2024-03-17.
//

#ifndef INC_3DVIEWERAPP_RENDERER_H
#define INC_3DVIEWERAPP_RENDERER_H


namespace v3D {

    class VertexArray;
    class IndexBuffer;
    class ShaderProgram;

    class Renderer {
    public:
        void draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
        void clear() const;
    };
} // v3D


#endif //INC_3DVIEWERAPP_RENDERER_H
