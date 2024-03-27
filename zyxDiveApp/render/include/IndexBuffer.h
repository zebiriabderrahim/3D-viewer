//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_ZYXDIVEAPP_INDEXBUFFER_H
#define INC_ZYXDIVEAPP_INDEXBUFFER_H

#include <GL/glew.h>

namespace zyxDive {

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

} // zyxDive

#endif //INC_ZYXDIVEAPP_INDEXBUFFER_H
