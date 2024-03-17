//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#include "ShaderProgram.h"
#include "Shader.h"
#include <spdlog/spdlog.h>

namespace v3D {

ShaderProgram::ShaderProgram() {
    programId_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programId_);
}

void ShaderProgram::initFromFiles(const char *vsPath, const char *fsPath) {
    v3D::Shader vs(GL_VERTEX_SHADER, vsPath);
    v3D::Shader fs(GL_FRAGMENT_SHADER, fsPath);

    attachShader(vs);
    attachShader(fs);

    link();

}

void ShaderProgram::initFromFiles(const char *vsPath, const char *gsPath, const char *fsPath) {
    v3D::Shader vs(GL_VERTEX_SHADER, vsPath);
    v3D::Shader gs(GL_GEOMETRY_SHADER, gsPath);
    v3D::Shader fs(GL_FRAGMENT_SHADER, fsPath);

    attachShader(vs);
    attachShader(gs);
    attachShader(fs);

    link();

}

void ShaderProgram::use() const {
    glUseProgram(programId_);
}

void ShaderProgram::attachShader(const v3D::Shader &shader) const {
    glAttachShader(programId_, shader.getShaderId());

}

void ShaderProgram::link() {
    glLinkProgram(programId_);
    checkProgramError();
}

GLint ShaderProgram::getAttribLocation(const std::string& name, bool verbose) const {
    GLint location = glGetAttribLocation(programId_, name.c_str());
    if (location == -1 && verbose) {
        spdlog::error("Attribute {} not found in shader program", name);
    }
    return location;
}

GLint ShaderProgram::getUniformLocation(const std::string& name){
    auto it = uniformLocationCache_.find(name);
    if (it != uniformLocationCache_.end()) {
        return it->second;
    }
    GLint location = glGetUniformLocation(programId_, name.c_str());
    if (location == -1) {
        spdlog::error("Uniform {} not found in shader program", name);
    }
    uniformLocationCache_[name] = location;
    return location;
}

void ShaderProgram::setUniformBlockBinding(const char *name, GLuint bindingIndex) {
    GLuint blockIndex = glGetUniformBlockIndex(programId_, name);
    if (blockIndex == GL_INVALID_INDEX) {
        spdlog::error("Uniform block {} not found in shader program", name);
    }
    glUniformBlockBinding(programId_, blockIndex, bindingIndex);
}

void ShaderProgram::setTransformFeedbackVaryings(const char **names, GLsizei count, GLenum mode) {
    glTransformFeedbackVaryings(programId_, count, names, mode);
    link();
}

void ShaderProgram::checkProgramError() const {
    int result;
    glGetProgramiv(programId_, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetProgramiv(programId_, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetProgramInfoLog(programId_, length, &length, message);
        spdlog::error("Failed to link shader program!");
        spdlog::error("{}", message);
        glDeleteProgram(programId_);
    }
}

} // v3D