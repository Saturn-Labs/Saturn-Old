#pragma once
#include "Event.h"
#include "Saturn/MouseButton.h"

namespace Saturn
{
	class SATURNAPI MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) { }

		inline float GetX()
		{
			return m_MouseX;
		}

		inline float GetY()
		{
			return m_MouseY;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class SATURNAPI MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) { }

		inline float GetXOffset() const
		{
			return m_XOffset;
		}

		inline float GetYOffset() const
		{
			return m_YOffset;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class SATURNAPI MouseButtonEvent : public Event
	{
	public:
		inline MouseButton GetMouseButton() const
		{
			return m_Button;
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput)
	protected:
		MouseButtonEvent(MouseButton button)
			: m_Button(button) { }

		MouseButton m_Button;
	};

	class SATURNAPI MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseButton button)
			: MouseButtonEvent(button) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << (int)m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class SATURNAPI MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseButton button)
			: MouseButtonEvent(button) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << (int)m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}