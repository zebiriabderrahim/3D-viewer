//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#ifndef INC_ZYXDIVEAPP_SHADERPROGRAM_H
#define INC_ZYXDIVEAPP_SHADERPROGRAM_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace zyxDive {

class Shader;

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    void initFromFiles(const char* vsPath, const char* fsPath);
    void initFromFiles(const char* vsPath, const char* gsPath, const char* fsPath);

    void use() const;
    void unuse() const;
    void attachShader(const Shader& shader) const;
    void link();

    [[nodiscard]] GLint getAttribLocation(const std::string& name, bool verbose = true);
    [[nodiscard]] GLint getUniformLocation(const std::string& name);

    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform2f(const std::string& name, float v0, float v1);
    void setUniform3f(const std::string& name, float v0, float v1, float v2);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniformMatrix4fv(const std::string& name, const glm::mat4& value);

    void setUniformBlockBinding(const char* name, GLuint bindingIndex) const;

    void setTransformFeedbackVaryings(const char** names, GLsizei count, GLenum mode);

private:
    void checkProgramError() const;

private:
    GLuint programId_;
    std::unordered_map<std::string, GLint> uniformLocationCache_;
    std::unordered_map<std::string, GLint> attribLocationCache_;
};

} // zyxDive
#endif //INC_ZYXDIVEAPP_SHADERPROGRAM_H
