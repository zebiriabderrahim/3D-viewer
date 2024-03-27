//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//

#include "ShaderProgram.h"
#include "Shader.h"
#include "Logger.h"


namespace zyxDive {

    ShaderProgram::ShaderProgram() {
        programId_ = glCreateProgram();
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(programId_);
    }

    void ShaderProgram::initFromFiles(const char *vsPath, const char *fsPath) {
        zyxDive::Shader vs(GL_VERTEX_SHADER, vsPath);
        zyxDive::Shader fs(GL_FRAGMENT_SHADER, fsPath);

        attachShader(vs);
        attachShader(fs);

        link();

    }

    void ShaderProgram::initFromFiles(const char *vsPath, const char *gsPath, const char *fsPath) {
        zyxDive::Shader vs(GL_VERTEX_SHADER, vsPath);
        zyxDive::Shader gs(GL_GEOMETRY_SHADER, gsPath);
        zyxDive::Shader fs(GL_FRAGMENT_SHADER, fsPath);

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

    void ShaderProgram::attachShader(const zyxDive::Shader &shader) const {
        glAttachShader(programId_, shader.getShaderId());

    }

    void ShaderProgram::link() {
        glLinkProgram(programId_);
        checkProgramError();
    }

    GLint ShaderProgram::getAttribLocation(const std::string &name, bool verbose) {
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

    GLint ShaderProgram::getUniformLocation(const std::string &name) {
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
        GLint result;
        glGetProgramiv(programId_, GL_LINK_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetProgramiv(programId_, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> errorLog(length);
            glGetProgramInfoLog(programId_, length, &length, &errorLog[0]);
            std::string errorMessage(&errorLog[0], length);

            std::istringstream stream(errorMessage);
            std::string line;
            while (std::getline(stream, line)) {
                LOG_ERROR("Failed to link program: {}", line);
            }

            glDeleteProgram(programId_);
        }
    }


    void ShaderProgram::setUniform1i(const std::string &name, int value) {
        glUniform1i(getUniformLocation(name), value);
    }

    void ShaderProgram::setUniform1f(const std::string &name, float value) {
        glUniform1f(getUniformLocation(name), value);
    }

    void ShaderProgram::setUniform2f(const std::string &name, float v0, float v1) {
        glUniform2f(getUniformLocation(name), v0, v1);
    }

    void ShaderProgram::setUniform3f(const std::string &name, float v0, float v1, float v2) {
        glUniform3f(getUniformLocation(name), v0, v1, v2);
    }

    void ShaderProgram::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
        glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
    }

    void ShaderProgram::setUniformMatrix4fv(const std::string &name, const glm::mat4 &value) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }
} // zyxDive