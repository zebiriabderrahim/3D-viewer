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
        void Unbind() const;

        [[nodiscard]] inline unsigned int getCount() const { return m_Count; }

    private:
        unsigned int m_RendererID;
        unsigned int m_Count;

    };

} // v3D

#endif //INC_3DVIEWERAPP_INDEXBUFFER_H
