#pragma once
#include "Saturn/KeyCode.h"
#include "Saturn/MouseButton.h"

namespace Saturn
{
	class SATURNAPI Input
	{
	public:
		inline static bool GetKeyPressed(Saturn::KeyCode keycode)
		{
			return s_Instance->GetKeyPressedImpl(keycode);
		}

		inline static bool GetMouseButtonPressed(Saturn::MouseButton button)
		{
			return s_Instance->GetMouseButtonPressedImpl(button);
		}

		inline static float GetMouseX()
		{
			return s_Instance->GetMouseXImpl();
		}

		inline static float GetMouseY()
		{
			return s_Instance->GetMouseYImpl();
		}
	protected:
		virtual bool GetKeyPressedImpl(Saturn::KeyCode keycode) = 0;
		virtual bool GetMouseButtonPressedImpl(Saturn::MouseButton button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	protected:
		static Input* s_Instance;
	};
}