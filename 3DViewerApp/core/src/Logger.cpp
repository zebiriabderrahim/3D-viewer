//
// Created by ABDERRAHIM ZEBIRI on 2024-03-25.
//

#include "Logger.h"

namespace v3D {


    Logger &Logger::getInstance() {
        static Logger instance;
        return instance;
    }

    std::string Logger::levelToString(Level level) {
        std::ostringstream stream;
        switch (level) {
            case Level::Info:
                stream << "[ " << GREEN << "INFO" << RESET << " ]";
                break;
            case Level::Warning:
                stream << "[ " << YELLOW << "WARNING" << RESET << " ]";
                break;
            case Level::Error:
                stream << "[ " << RED << "ERROR" << RESET << " ]";
                break;
            default:
                stream << RESET << "UNKNOWN";
        }
        return stream.str();
    }

    std::string Logger::getFormattedTime() {
        std::ostringstream stream;
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        stream << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
                << '.' << std::setfill('0')
                << std::setw(3)<< milliseconds.count();
        return stream.str();
    }
} // v3D