#pragma once
#include "Saturn/Input.h"

namespace Saturn
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool GetKeyPressedImpl(Saturn::KeyCode keycode) override final;
		virtual bool GetMouseButtonPressedImpl(Saturn::MouseButton button) override final;
		virtual float GetMouseXImpl() override final;
		virtual float GetMouseYImpl() override final;
	};
}

