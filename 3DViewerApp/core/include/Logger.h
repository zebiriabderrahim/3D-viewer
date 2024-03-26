//
// Created by ABDERRAHIM ZEBIRI on 2024-03-25.
//

#ifndef INC_3DVIEWERAPP_LOGGER_H
#define INC_3DVIEWERAPP_LOGGER_H

#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

namespace v3D {

    enum class Level {
        Info,
        Warning,
        Error
    };

    class Logger {

    public:
        static Logger &getInstance();

        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;


        template<typename... Args>
        static void info(const std::string &format, Args... args) {
            getInstance().log(Level::Info, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void warning(const std::string &format, Args... args) {
            getInstance().log(Level::Warning, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void error(const std::string &format, Args... args) {
            getInstance().log(Level::Error, format, std::forward<Args>(args)...);
        }

    private:
        Logger() = default;

        std::mutex mutex_;


        static std::string levelToString(Level level);

        static std::string getFormattedTime();

        template<typename... Args>
        void log(Level level, const std::string &format, Args... args) {
            std::ostringstream stream;

            stream << getFormattedTime() << " " << levelToString(level)
                   << " " << formatString(format, std::forward<Args>(args)...)
                   << RESET << std::endl;

            {
                std::lock_guard<std::mutex> guard(mutex_);
                std::cout << stream.str();
            }
        }

        template<typename... Args>
        std::string formatString(const std::string &format, Args... args) {
            std::ostringstream stream;
            formatImpl(stream, format, std::forward<Args>(args)...);
            return stream.str();
        }

        template<typename T, typename... Args>
        void formatImpl(std::ostringstream &stream, const std::string &format, T value, Args... args) {
            size_t pos = format.find("{}");
            if (pos != std::string::npos) {
                stream << format.substr(0, pos) << value;
                formatImpl(stream, format.substr(pos + 2), std::forward<Args>(args)...);
            } else {
                stream << format; // Append the remainder of the format string
            }
        }

        // Base case for recursion
        static void formatImpl(std::ostringstream &stream, const std::string &format) {
            stream << format;
        }
    };

#define LOG_INFO(...) v3D::Logger::info(__VA_ARGS__)
#define LOG_WARNING(...) v3D::Logger::warning(__VA_ARGS__)
#define LOG_ERROR(...) v3D::Logger::error(__VA_ARGS__)

} // namespace v3D

#endif //INC_3DVIEWERAPP_LOGGER_H
