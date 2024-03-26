//
// Created by ABDERRAHIM ZEBIRI on 2024-03-25.
//

#include "Logger.h"

namespace v3D {


    Logger &Logger::getInstance() {
        static Logger instance;
        return instance;
    }

    void Logger::levelToString(std::ostringstream &stream, Level level) {
        switch (level) {
            case Level::Info:
                stream <<"[ "<< GREEN << "INFO" << RESET << " ]";
                break;
            case Level::Warning:
                stream <<"[ "<< YELLOW << "WARNING" << RESET << " ]";
                break;
            case Level::Error:
                stream << "[ " << RED << "ERROR" << RESET << " ]";
                break;
            default:
                stream << RESET << "UNKNOWN";
        }
    }
} // v3D