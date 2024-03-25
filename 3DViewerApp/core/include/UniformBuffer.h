//
// Created by ABDERRAHIM ZEBIRI on 2024-03-24.
//

#ifndef INC_3DVIEWERAPP_UNIFORMBUFFER_H
#define INC_3DVIEWERAPP_UNIFORMBUFFER_H

#include <GL/glew.h>

namespace v3D {

    class UniformBuffer {

    public:
        UniformBuffer(const void *data, GLuint size);
        ~UniformBuffer();

        void bind() const;
        void bindWithIndex(GLuint index) const;
        void setData(const void *data, GLuint size) const;

    private:
        GLuint rendererID_;
    };

} // v3D

#endif //INC_3DVIEWERAPP_UNIFORMBUFFER_H
