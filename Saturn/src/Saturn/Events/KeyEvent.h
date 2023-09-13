#pragma once
#include "Event.h"

namespace Saturn
{
	class SATURNAPI KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const
		{
			m_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) { }

		int m_KeyCode;
	};

	class SATURNAPI KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const
		{
			return m_RepeatCount;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class SATURNAPI KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}