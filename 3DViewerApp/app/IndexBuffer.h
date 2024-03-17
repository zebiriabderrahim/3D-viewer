//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_3DVIEWERAPP_INDEXBUFFER_H
#define INC_3DVIEWERAPP_INDEXBUFFER_H

#include <GL/glew.h>

namespace v3D {

    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int *data, GLuint count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        [[nodiscard]] inline unsigned int getCount() const { return count_; }

    private:
        unsigned int rendererID_;
        unsigned int count_;
    };

} // v3D

#endif //INC_3DVIEWERAPP_INDEXBUFFER_H
