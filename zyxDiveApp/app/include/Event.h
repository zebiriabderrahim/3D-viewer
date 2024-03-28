//
// Created by ABDERRAHIM ZEBIRI on 2024-03-27.
//

#ifndef ZYXDIVEAPP_EVENT_H
#define ZYXDIVEAPP_EVENT_H

#include <functional>
#include <string>


namespace zyxDive {

    enum class EventType {
        None = 0,
        MouseMovedEvent, MouseScrolledEvent, MouseButtonPressedEvent, MouseButtonReleasedEvent,
        KeyPressedEvent, KeyReleasedEvent,
        WindowResizeEvent, WindowCloseEvent,
        AppTickEvent, AppUpdateEvent, AppRenderEvent,
    };

    enum class EventCategory {
        None = 0,
        Application = 1 << 0,
        Input = 1 << 1,
        Keyboard = 1 << 2,
        Mouse = 1 << 2,
        MouseButton = 1 << 2
    };


    class Event {
    public:
        bool handled = false;

        virtual ~Event() = default;

        [[nodiscard]] virtual EventType getEventType() const = 0;

        [[nodiscard]] virtual std::string getName() const = 0;

        [[nodiscard]] virtual int getCategoryFlags() const = 0;

        [[nodiscard]] virtual std::string toString() const { return getName(); }

        [[nodiscard]] bool isInCategory(EventCategory category) const {
            return getCategoryFlags() & static_cast<int>(category);
        }
    };

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T &)>;

    public:
        explicit EventDispatcher(Event &event) : m_Event(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if (auto derivedEvent = dynamic_cast<T *>(&m_Event)) {
                m_Event.handled = func(*derivedEvent);
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.toString();
    }

} // zyxDive

#endif //ZYXDIVEAPP_EVENT_H
