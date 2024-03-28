//
// Created by ABDERRAHIM ZEBIRI on 2024-03-27.
//

#ifndef ZYXDIVEAPP_APPEVENT_H
#define ZYXDIVEAPP_APPEVENT_H

#include "Event.h"
#include <sstream>

namespace zyxDive {

    class WindowResizeEvent : public Event {

        public:
        WindowResizeEvent(unsigned int width, unsigned int height) : width_(width), height_(height) {}

        static EventType getStaticType() { return EventType::WindowResizeEvent; }

        [[nodiscard]] std::string getName() const override { return "WindowResize"; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Application);
        }

        [[nodiscard]] unsigned int getWidth() const { return width_; }

        [[nodiscard]] unsigned int getHeight() const { return height_; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << width_ << ", " << height_;
            return ss.str();
        }

        private:
        unsigned int width_, height_;
    };

    class WindowCloseEvent : public Event {

        public:
        WindowCloseEvent() = default;

        static EventType getStaticType() { return EventType::WindowCloseEvent; }

        [[nodiscard]] std::string getName() const override { return "WindowClose"; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Application);
        }
    };

    class AppTickEvent : public Event {

        public:
        AppTickEvent() = default;

        static EventType getStaticType() { return EventType::AppTickEvent; }

        [[nodiscard]] std::string getName() const override { return "AppTick"; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Application);
        }
    };

    class AppUpdateEvent : public Event {

        public:
        AppUpdateEvent() = default;

        static EventType getStaticType() { return EventType::AppUpdateEvent; }

        [[nodiscard]] std::string getName() const override { return "AppUpdate"; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Application);
        }
    };

    class AppRenderEvent : public Event {

        public:
        AppRenderEvent() = default;

        static EventType getStaticType() { return EventType::AppRenderEvent; }

        [[nodiscard]] std::string getName() const override { return "AppRender"; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Application);
        }
    };

} // zyxDive

#endif //ZYXDIVEAPP_APPEVENT_H
