//
// Created by ABDERRAHIM ZEBIRI on 2024-03-17.
//

#ifndef INC_ZYXDIVEAPP_RENDERER_H
#define INC_ZYXDIVEAPP_RENDERER_H


namespace zyxDive {

    class VertexArray;
    class IndexBuffer;
    class ShaderProgram;

    class Renderer {
    public:
        void draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
        void clear() const;
    };
} // zyxDive


#endif //INC_ZYXDIVEAPP_RENDERER_H
