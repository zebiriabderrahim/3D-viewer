//
// Created by ABDERRAHIM ZEBIRI on 2024-03-27.
//

#ifndef ZYXDIVEAPP_KEYEVENT_H
#define ZYXDIVEAPP_KEYEVENT_H

#include <string>
#include <sstream>
#include "Event.h"
#include "KeyCodes.h"

namespace zyxDive {
    class KeyEvent : public Event {
    public:
        [[nodiscard]] Key::KeyCode getKeyCode() const { return keyCode_; }

        [[nodiscard]] int getCategoryFlags() const override {
            return static_cast<int>(EventCategory::Keyboard) | static_cast<int>(EventCategory::Input);
        }

    protected:
        explicit KeyEvent(const Key::KeyCode keycode) : keyCode_(keycode) {}

        Key::KeyCode keyCode_;
    };


    class KeyPressedEvent : public KeyEvent {
    public:
        explicit KeyPressedEvent(const Key::KeyCode keycode, bool isRepeat = false) : KeyEvent(keycode),
                                                                                      isRepeat_(isRepeat) {}

        [[nodiscard]] bool IsRepeat() const { return isRepeat_; }

        static EventType getStaticType() { return EventType::KeyPressedEvent; }

        [[nodiscard]] std::string getName() const override { return "KeyPressed"; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << static_cast<int>(keyCode_) << " (repeat = " << isRepeat_ << ")";
            return ss.str();
        }

    private:
        bool isRepeat_;
    };


    class KeyReleasedEvent : public KeyEvent {
    public:
        explicit KeyReleasedEvent(const Key::KeyCode keycode) : KeyEvent(keycode) {}

        static EventType getStaticType() { return EventType::KeyReleasedEvent; }

        [[nodiscard]] std::string getName() const override { return "KeyReleased"; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << static_cast<int>(keyCode_);
            return ss.str();
        }

    };


} // zyxDive

#endif //ZYXDIVEAPP_KEYEVENT_H
