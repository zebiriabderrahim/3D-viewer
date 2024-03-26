//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#include "ShaderProgram.h"
#include "Shader.h"
#include "Logger.h"


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

void ShaderProgram::unuse() const {
    glUseProgram(0);
}

void ShaderProgram::attachShader(const v3D::Shader &shader) const {
    glAttachShader(programId_, shader.getShaderId());

}

void ShaderProgram::link() {
    glLinkProgram(programId_);
    checkProgramError();
}

GLint ShaderProgram::getAttribLocation(const std::string& name, bool verbose){
    auto it = attribLocationCache_.find(name);
    if (it != attribLocationCache_.end()) {
        return it->second;
    }
    GLint location = glGetAttribLocation(programId_, name.c_str());
    if (location == -1 && verbose) {
        LOG_ERROR("Attribute {} not found in shader program", name);
    }
    attribLocationCache_[name] = location;
    return location;
}

GLint ShaderProgram::getUniformLocation(const std::string& name){
    auto it = uniformLocationCache_.find(name);
    if (it != uniformLocationCache_.end()) {
        return it->second;
    }
    GLint location = glGetUniformLocation(programId_, name.c_str());
    if (location == -1) {
        LOG_ERROR("Uniform {} not found in shader program", name);
    }
    uniformLocationCache_[name] = location;
    return location;
}

void ShaderProgram::setUniformBlockBinding(const char *name, GLuint bindingIndex) const {
    GLuint blockIndex = glGetUniformBlockIndex(programId_, name);
    if (blockIndex == GL_INVALID_INDEX) {
        LOG_ERROR("Uniform block {} not found in shader program", name);
    }
    glUniformBlockBinding(programId_, blockIndex, bindingIndex);
}


void ShaderProgram::checkProgramError() const {
    int result;
    glGetProgramiv(programId_, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetProgramiv(programId_, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetProgramInfoLog(programId_, length, &length, message);
        LOG_ERROR("Failed to link program: {}", message);
        glDeleteProgram(programId_);
    }
}

    void ShaderProgram::setUniform1i(const std::string& name, int value) {
        glUniform1i(getUniformLocation(name), value);
    }

    void ShaderProgram::setUniform1f(const std::string& name, float value) {
        glUniform1f(getUniformLocation(name), value);
    }

    void ShaderProgram::setUniform2f(const std::string& name, float v0, float v1) {
        glUniform2f(getUniformLocation(name), v0, v1);
    }

    void ShaderProgram::setUniform3f(const std::string& name, float v0, float v1, float v2) {
        glUniform3f(getUniformLocation(name), v0, v1, v2);
    }

    void ShaderProgram::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
    }

    void ShaderProgram::setUniformMatrix4fv(const std::string& name, const glm::mat4 &value) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }
} // v3D