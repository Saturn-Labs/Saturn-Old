#pragma once
#include "Saturn/Input/KeyCode.h"
#include "Saturn/Input/MouseButton.h"
#include "glm/glm.hpp"

namespace Saturn
{
	enum class InputState : char
	{
		NullState = 0,
		Down,
		Up
	};

	class Input
	{
		friend class WindowsWindow;
	public:
		inline static glm::vec2 MousePosition = glm::vec2(0.0f);
		inline static glm::vec2 MouseScrollDelta = glm::vec2(0.0f);
	
	public:

		inline static InputState GetKeyCurrentState(Saturn::KeyCode keycode)
		{
			if (s_StateKeyMap.find(keycode) == s_StateKeyMap.end())
				s_StateKeyMap[keycode] = InputState::Up;

			return s_StateKeyMap[keycode];
		}
		inline static bool GetKeyRepeat(Saturn::KeyCode keycode)
		{
			if (s_RepeatKeyMap.find(keycode) == s_RepeatKeyMap.end())
				s_RepeatKeyMap[keycode] = InputState::NullState;

			return s_RepeatKeyMap[keycode] == InputState::Down;
		}
		inline static bool GetKeyDown(Saturn::KeyCode keycode)
		{
			if (s_FrameKeyMap.find(keycode) == s_FrameKeyMap.end())
				s_FrameKeyMap[keycode] = InputState::NullState;

			return s_FrameKeyMap[keycode] == InputState::Down;
		}
		inline static bool GetKeyUp(Saturn::KeyCode keycode)
		{
			if (s_FrameKeyMap.find(keycode) == s_FrameKeyMap.end())
				s_FrameKeyMap[keycode] = InputState::NullState;

			return s_FrameKeyMap[keycode] == InputState::Up;
		}

		inline static InputState GetMouseButtonCurrentState(Saturn::MouseButton button)
		{
			if (s_StateMouseButtonMap.find(button) == s_StateMouseButtonMap.end())
				s_StateMouseButtonMap[button] = InputState::Up;

			return s_StateMouseButtonMap[button];
		}
		inline static bool GetMouseButtonDown(Saturn::MouseButton button)
		{
			if (s_FrameMouseButtonMap.find(button) == s_FrameMouseButtonMap.end())
				s_FrameMouseButtonMap[button] = InputState::NullState;

			return s_FrameMouseButtonMap[button] == InputState::Down;
		}
		inline static bool GetMouseButtonUp(Saturn::MouseButton button)
		{
			if (s_FrameMouseButtonMap.find(button) == s_FrameMouseButtonMap.end())
				s_FrameMouseButtonMap[button] = InputState::NullState;

			return s_FrameMouseButtonMap[button] == InputState::Up;
		}

		inline static const glm::vec2& GetMousePosition()
		{
			return MousePosition;
		}
		inline static const glm::vec2& GetMouseScrollDelta()
		{
			return MouseScrollDelta;
		}

		inline static void ResetKeyStates()
		{
			for (auto& [key, state] : s_FrameKeyMap)
				state = InputState::NullState;

			for (auto& [key, state] : s_RepeatKeyMap)
				state = InputState::NullState;

			for (auto& [key, state] : s_FrameMouseButtonMap)
				state = InputState::NullState;
		}

		inline static std::unordered_map<Saturn::KeyCode, InputState>& GetFrameKeyMap()
		{
			return s_FrameKeyMap;
		}
		inline static std::unordered_map<Saturn::KeyCode, InputState>& GetStateKeyMap()
		{
			return s_StateKeyMap;
		}
		inline static std::unordered_map<Saturn::KeyCode, InputState>& GetRepeatKeyMap()
		{
			return s_RepeatKeyMap;
		}
		inline static std::unordered_map<Saturn::MouseButton, InputState>& GetFrameMouseButtonMap()
		{
			return s_FrameMouseButtonMap;
		}
		inline static std::unordered_map<Saturn::MouseButton, InputState>& GetStateMouseButtonMap()
		{
			return s_StateMouseButtonMap;
		}

	protected:
		inline static std::unordered_map<Saturn::KeyCode, InputState> s_FrameKeyMap;
		inline static std::unordered_map<Saturn::KeyCode, InputState> s_StateKeyMap;
		inline static std::unordered_map<Saturn::KeyCode, InputState> s_RepeatKeyMap;

		inline static std::unordered_map<Saturn::MouseButton, InputState> s_FrameMouseButtonMap;
		inline static std::unordered_map<Saturn::MouseButton, InputState> s_StateMouseButtonMap;
	};
}