#pragma once
#include "SaturnPch.h"
#include "Saturn/Events/Event.h"
#include "Saturn/Core/Core.h"
#include "Saturn/Core/Time.h"

namespace Saturn
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate(Time time) { }
		virtual void OnImGuiRender() { }
		virtual void OnEvent(Event& event) { }

		inline const std::string& GetDebugName() const
		{
			return m_DebugName;
		}
	protected:
		std::string m_DebugName;
	};
}