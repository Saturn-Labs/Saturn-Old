#pragma once
#include "saturnpch.h"
#include "EventType.h"
#include "EventCategory.h"

namespace Saturn
{
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
							   virtual EventType GetEventType() const override { return GetStaticType(); } \
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class SATURNAPI Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const
		{
			return GetName();
		}

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T = Event>
		using EventFn = std::is_function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) { }

		template<typename T = Event>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}
}