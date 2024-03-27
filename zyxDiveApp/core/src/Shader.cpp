//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Logger.h"


namespace zyxDive {
    Shader::Shader(GLenum type, const std::string& filepath) {
        shaderId_ = glCreateShader(type);
        const std::string& source = parseShader(filepath);
        const char *src = source.c_str();
        glShaderSource(shaderId_, 1, &src, nullptr);
        glCompileShader(shaderId_);
        checkShaderError();
    }

    Shader::~Shader() {
        glDeleteShader(shaderId_);
    }

    GLuint Shader::getShaderId() const {
        return shaderId_;
    }

    void Shader::checkShaderError() const {
        int result;
        glGetShaderiv(shaderId_, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(shaderId_, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *) alloca(length * sizeof(char));
            glGetShaderInfoLog(shaderId_, length, &length, message);
            LOG_ERROR("Failed to compile shader: {}", message);
            glDeleteShader(shaderId_);
        }
    }

    std::string Shader::parseShader(const std::string& filepath) {
        try {
            std::ifstream stream(filepath);
            if (!stream.is_open()) {
                throw std::runtime_error("Failed to open file: " + filepath);
            }
            std::stringstream ss;
            ss << stream.rdbuf();
            return ss.str();
        } catch (const std::exception& e) {
            LOG_ERROR("Failed to parse shader: {}", e.what());
            return "";
        }
    }

} // zyxDive