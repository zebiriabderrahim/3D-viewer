//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_3DVIEWERAPP_VERTEXBUFFER_H
#define INC_3DVIEWERAPP_VERTEXBUFFER_H

#include <GL/glew.h>


namespace v3D {

    class VertexBuffer {

    public:
        VertexBuffer(const float *data, GLuint size);
        ~VertexBuffer();
        void bind() const;
        void Unbind() const;

    private:
        unsigned int rendererID_;

    };

} // v3D

#endif //INC_3DVIEWERAPP_VERTEXBUFFER_H
