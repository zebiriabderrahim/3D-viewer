//
// Created by ABDERRAHIM ZEBIRI on 2024-03-16.
//
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include "Shader.h"

namespace v3D {
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
            spdlog::error("Failed to compile shader!");
            spdlog::error("{}", message);
            glDeleteShader(shaderId_);
        }
    }

    std::string Shader::parseShader(const std::string& filepath) {
        std::ifstream stream(filepath);
        //error handling
        if (!stream) {
            spdlog::error("Failed to open file {}", filepath);
        }
        std::string line;
        std::stringstream ss;
        while (getline(stream, line)) {
            ss << line << '\n';
        }
        return ss.str();
    }

} // v3D