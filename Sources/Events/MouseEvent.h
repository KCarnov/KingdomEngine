#pragma once
#include "Events.h"


    //MOUSE MOVED EVENT
    class  MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float x, const float y)
            : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }


        EVENT_CLASS_TYPE(MouseMoved)
        //EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_MouseX, m_MouseY;
    };


    //MOUSE SCROLLED EVENT
    class  MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        EVENT_CLASS_TYPE(MouseScrolled)
        //EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_XOffset, m_YOffset;
    };

    //MOUSE BUTTON PRESSED EVENT
    class  MouseButtonPressedEvent : public Event
    {
    public:MouseButtonPressedEvent(const int button)
            : m_Button(button) {}

        int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_TYPE(MouseButtonPressed)

    private:
        int m_Button;
    };


    //MOUSE BUTTON RELEASED EVENT
    class  MouseButtonReleasedEvent : public Event
    {
    public:MouseButtonReleasedEvent(const int button)
        : m_Button(button) {}

          int GetMouseButton() const { return m_Button; }

          EVENT_CLASS_TYPE(MouseButtonReleased)

    private:
        int m_Button;
    };