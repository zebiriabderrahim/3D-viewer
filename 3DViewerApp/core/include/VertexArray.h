//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_3DVIEWERAPP_VERTEXARRAY_H
#define INC_3DVIEWERAPP_VERTEXARRAY_H

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace v3D {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;

        void bind() const;
        void unbind() const;

    private:
        unsigned int rendererID_;

    };

} // v3D

#endif //INC_3DVIEWERAPP_VERTEXARRAY_H
