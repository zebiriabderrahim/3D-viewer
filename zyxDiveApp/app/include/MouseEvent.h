//
// Created by ABDERRAHIM ZEBIRI on 2024-03-27.
//

#ifndef ZYXDIVEAPP_MOUSEEVENT_H
#define ZYXDIVEAPP_MOUSEEVENT_H

#include <sstream>
#include <cstdint>
#include <string>
#include "Event.h"

namespace zyxDive {

    enum class MouseCode : uint16_t {
        ButtonLeft = 0,
        ButtonRight = 1,
        ButtonMiddle = 2,
        ButtonLast = ButtonMiddle
    };

    class MouseMovedEvent : public Event {

    public:
        MouseMovedEvent(float x, float y) : mouseX_(x), mouseY_(y) {}

        static EventType getStaticType() { return EventType::MouseMovedEvent; }

        [[nodiscard]] std::string getName() const override { return "MouseMoved"; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse);
        }

        [[nodiscard]] float getX() const { return mouseX_; }

        [[nodiscard]] float getY() const { return mouseY_; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mouseX_ << ", " << mouseY_;
            return ss.str();
        }

    private:
        float mouseX_, mouseY_;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : xOffset_(xOffset), yOffset_(yOffset) {}

        static EventType GetStaticType() { return EventType::MouseScrolledEvent; }

        [[nodiscard]] std::string getName() const override { return "MouseScrolled"; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse);
        }

        [[nodiscard]] float getXOffset() const { return xOffset_; }

        [[nodiscard]] float getYOffset() const { return yOffset_; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
            return ss.str();
        }

    private:
        float xOffset_, yOffset_;
    };


    class MouseButtonEvent : public Event {
    public:
        [[nodiscard]] MouseCode getMouseButton() const { return button_; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse) |
                   static_cast<int>(EventCategory::MouseButton);
        }

    protected:
        explicit MouseButtonEvent(MouseCode button) : button_(button) {}

        MouseCode button_;

    };


    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}

        static EventType GetStaticType() { return EventType::MouseButtonPressedEvent; }

        [[nodiscard]] std::string getName() const override { return "MouseButtonPressed"; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << static_cast<int>(button_);
            return ss.str();
        }
    };


    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}

        static EventType getStaticType() { return EventType::MouseButtonReleasedEvent; }

        [[nodiscard]] std::string getName() const override { return "MouseButtonReleased"; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << static_cast<int>(button_);
            return ss.str();
        }
    };
} // zyxDive
#endif //ZYXDIVEAPP_MOUSEEVENT_H
