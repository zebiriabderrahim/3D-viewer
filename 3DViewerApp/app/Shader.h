//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_3DVIEWERAPP_SHADER_H
#define INC_3DVIEWERAPP_SHADER_H

#include <GL/glew.h>
#include <string>


namespace v3D {

    class Shader {
    public:
        Shader(GLenum type, const std::string& filepath);
        ~Shader();

        GLuint getShaderId() const;

    private:
        void checkShaderError() const;
        [[nodiscard]] static std::string parseShader(const std::string& filepath) ;

    private:
        GLuint shaderId_;
    };
} // v3D

#endif //INC_3DVIEWERAPP_SHADER_H
