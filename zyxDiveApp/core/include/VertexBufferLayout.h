//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_ZYXDIVEAPP_VERTEXBUFFERLAYOUT_H
#define INC_ZYXDIVEAPP_VERTEXBUFFERLAYOUT_H
#include <GL/glew.h>
#include <vector>
#include <stdexcept>

namespace zyxDive {

    // Represents a single element in a vertex buffer
    struct VertexBufferElement {
        GLuint type;
        unsigned int count;
        GLboolean isNormalized;

        // Returns the size in bytes of a given OpenGL type
        static unsigned int getSizeOfType(GLuint type) {
            switch (type) {
                case GL_FLOAT:
                case GL_UNSIGNED_INT:
                    return 4;
                case GL_UNSIGNED_BYTE:
                    return 1;
                default:
                    throw std::invalid_argument("Unsupported type in VertexBufferElement");
            }
        }
    };

    // Manages the layout of a vertex buffer
    class VertexBufferLayout {

    public:
        VertexBufferLayout() : stride_(0) {}

        // Adds an element to the vertex buffer layout
        template<typename T>
        void addElement(unsigned int count) {
            static_assert(std::is_same<T, float>::value ||
                          std::is_same<T, unsigned int>::value ||
                          std::is_same<T, unsigned char>::value,
                          "Unsupported type for VertexBufferLayout::addElement");
        }

        // Specialization for float
        template<>
        void addElement<float>(unsigned int count) {
            elements_.push_back({GL_FLOAT, count, GL_FALSE});
            stride_ += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
        }

        // Specialization for unsigned int
        template<>
        void addElement<unsigned int>(unsigned int count) {
            elements_.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
        }

        // Specialization for unsigned char
        template<>
        void addElement<unsigned char>(unsigned int count) {
            elements_.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
        }

        // Returns a const reference to the elements vector
        [[nodiscard]] const std::vector<VertexBufferElement>& getElements() const { return elements_; }

        // Returns the stride of the layout
        [[nodiscard]] GLuint getStride() const { return stride_; }

    private:
        std::vector<VertexBufferElement> elements_;
        GLuint stride_;
    };

} // zyxDive

#endif //INC_ZYXDIVEAPP_VERTEXBUFFERLAYOUT_H
