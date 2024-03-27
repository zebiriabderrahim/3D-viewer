//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_ZYXDIVEAPP_VERTEXBUFFER_H
#define INC_ZYXDIVEAPP_VERTEXBUFFER_H

#include <GL/glew.h>


namespace zyxDive {

    class VertexBuffer {

    public:
        VertexBuffer(const float *data, GLuint size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

    private:
        unsigned int rendererID_;

    };

} // zyxDive

#endif //INC_ZYXDIVEAPP_VERTEXBUFFER_H
