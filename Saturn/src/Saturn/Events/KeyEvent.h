#pragma once
#include "Event.h"
#include "Saturn/KeyCode.h"

namespace Saturn
{
	class SATURNAPI KeyEvent : public Event
	{
	public:
		inline Saturn::KeyCode GetKeyCode() const
		{
			return m_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(Saturn::KeyCode keycode)
			: m_KeyCode(keycode) { }

		Saturn::KeyCode m_KeyCode;
	};

	class SATURNAPI KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(Saturn::KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const
		{
			return m_RepeatCount;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << (int)m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class SATURNAPI KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(Saturn::KeyCode keycode)
			: KeyEvent(keycode) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << (int)m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class SATURNAPI KeyTypedEvent : public Event
	{
	public:
		KeyTypedEvent(int character)
			: m_Character(character)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: '" << (char)m_Character << "'";
			return ss.str();
		}

		inline unsigned int GetCharacter() const
		{
			return m_Character;
		}

		EVENT_CLASS_TYPE(KeyTyped)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	private:
		unsigned int m_Character;
	};
}