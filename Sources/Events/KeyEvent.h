#pragma once

#include "Events.h"

class KeyPressedEvent : public Event {
public:
	KeyPressedEvent(const int keycode, int repeatedCount)
		:m_KeyCode(keycode), m_repeatedCount(repeatedCount) {}

	inline int GetKeyCode() const { return m_KeyCode; }
	inline int GetRepeatedCount() const { return m_repeatedCount; }
	EVENT_CLASS_TYPE(KeyPressed)
private:
	int m_KeyCode;
	int m_repeatedCount;
};


class KeyReleasedEvent : public Event {
public:
	KeyReleasedEvent(const int keycode)
		:m_KeyCode(keycode) {}

	inline int GetKeyCode() const { return m_KeyCode; }
	EVENT_CLASS_TYPE(KeyReleased)
private:
	int m_KeyCode;
};

class KeyTypedEvent : public Event {
public:
	KeyTypedEvent(const int keycode, int repeatedCount)
		:m_KeyCode(keycode) {}

	inline int GetKeyCode() const { return m_KeyCode; }
	EVENT_CLASS_TYPE(KeyTyped)
private:
	int m_KeyCode;
};
