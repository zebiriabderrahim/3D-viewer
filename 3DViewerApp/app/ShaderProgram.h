//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_3DVIEWERAPP_SHADERPROGRAM_H
#define INC_3DVIEWERAPP_SHADERPROGRAM_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>

namespace v3D {

class Shader;

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    void initFromFiles(const char* vsPath, const char* fsPath);
    void initFromFiles(const char* vsPath, const char* gsPath, const char* fsPath);

    void use() const;
    void attachShader(const Shader& shader) const;
    void link();

    [[nodiscard]] GLint getAttribLocation(const std::string& name, bool verbose = true) const;
    [[nodiscard]] GLint getUniformLocation(const std::string& name);
    void setUniformBlockBinding(const char* name, GLuint bindingIndex);

    void setTransformFeedbackVaryings(const char** names, GLsizei count, GLenum mode);

private:
    void checkProgramError() const;

private:
    GLuint programId_;
    std::unordered_map<std::string, GLint> uniformLocationCache_;


};

} // v3D
#endif //INC_3DVIEWERAPP_SHADERPROGRAM_H
