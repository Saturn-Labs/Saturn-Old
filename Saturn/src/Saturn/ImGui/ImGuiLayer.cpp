#include "saturnpch.h"
#include "ImGuiLayer.h"
#include "Saturn/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

//TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Saturn
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		float time = glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		static bool show = true;
		if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Insert, false))
			show = !show;

		if (show)
			ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<MouseMovedEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ST_BIND_EVENTFN(&ImGuiLayer::OnWindowResizeEvent));
	}

	inline ImGuiKey ImGuiLayer::GetImGuiKeyForKeyCode(Saturn::KeyCode keycode)
    {
        switch ((int)keycode)
        {
            case GLFW_KEY_TAB: return ImGuiKey_Tab;
            case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
            case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
            case GLFW_KEY_UP: return ImGuiKey_UpArrow;
            case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
            case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
            case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
            case GLFW_KEY_HOME: return ImGuiKey_Home;
            case GLFW_KEY_END: return ImGuiKey_End;
            case GLFW_KEY_INSERT: return ImGuiKey_Insert;
            case GLFW_KEY_DELETE: return ImGuiKey_Delete;
            case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
            case GLFW_KEY_SPACE: return ImGuiKey_Space;
            case GLFW_KEY_ENTER: return ImGuiKey_Enter;
            case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
            case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
            case GLFW_KEY_COMMA: return ImGuiKey_Comma;
            case GLFW_KEY_MINUS: return ImGuiKey_Minus;
            case GLFW_KEY_PERIOD: return ImGuiKey_Period;
            case GLFW_KEY_SLASH: return ImGuiKey_Slash;
            case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
            case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
            case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
            case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
            case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
            case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
            case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
            case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
            case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
            case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
            case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
            case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
            case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
            case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
            case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
            case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
            case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
            case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
            case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
            case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
            case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
            case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
            case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
            case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
            case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
            case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
            case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
            case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
            case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
            case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
            case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
            case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
            case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
            case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
            case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
            case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
            case GLFW_KEY_MENU: return ImGuiKey_Menu;
            case GLFW_KEY_0: return ImGuiKey_0;
            case GLFW_KEY_1: return ImGuiKey_1;
            case GLFW_KEY_2: return ImGuiKey_2;
            case GLFW_KEY_3: return ImGuiKey_3;
            case GLFW_KEY_4: return ImGuiKey_4;
            case GLFW_KEY_5: return ImGuiKey_5;
            case GLFW_KEY_6: return ImGuiKey_6;
            case GLFW_KEY_7: return ImGuiKey_7;
            case GLFW_KEY_8: return ImGuiKey_8;
            case GLFW_KEY_9: return ImGuiKey_9;
            case GLFW_KEY_A: return ImGuiKey_A;
            case GLFW_KEY_B: return ImGuiKey_B;
            case GLFW_KEY_C: return ImGuiKey_C;
            case GLFW_KEY_D: return ImGuiKey_D;
            case GLFW_KEY_E: return ImGuiKey_E;
            case GLFW_KEY_F: return ImGuiKey_F;
            case GLFW_KEY_G: return ImGuiKey_G;
            case GLFW_KEY_H: return ImGuiKey_H;
            case GLFW_KEY_I: return ImGuiKey_I;
            case GLFW_KEY_J: return ImGuiKey_J;
            case GLFW_KEY_K: return ImGuiKey_K;
            case GLFW_KEY_L: return ImGuiKey_L;
            case GLFW_KEY_M: return ImGuiKey_M;
            case GLFW_KEY_N: return ImGuiKey_N;
            case GLFW_KEY_O: return ImGuiKey_O;
            case GLFW_KEY_P: return ImGuiKey_P;
            case GLFW_KEY_Q: return ImGuiKey_Q;
            case GLFW_KEY_R: return ImGuiKey_R;
            case GLFW_KEY_S: return ImGuiKey_S;
            case GLFW_KEY_T: return ImGuiKey_T;
            case GLFW_KEY_U: return ImGuiKey_U;
            case GLFW_KEY_V: return ImGuiKey_V;
            case GLFW_KEY_W: return ImGuiKey_W;
            case GLFW_KEY_X: return ImGuiKey_X;
            case GLFW_KEY_Y: return ImGuiKey_Y;
            case GLFW_KEY_Z: return ImGuiKey_Z;
            case GLFW_KEY_F1: return ImGuiKey_F1;
            case GLFW_KEY_F2: return ImGuiKey_F2;
            case GLFW_KEY_F3: return ImGuiKey_F3;
            case GLFW_KEY_F4: return ImGuiKey_F4;
            case GLFW_KEY_F5: return ImGuiKey_F5;
            case GLFW_KEY_F6: return ImGuiKey_F6;
            case GLFW_KEY_F7: return ImGuiKey_F7;
            case GLFW_KEY_F8: return ImGuiKey_F8;
            case GLFW_KEY_F9: return ImGuiKey_F9;
            case GLFW_KEY_F10: return ImGuiKey_F10;
            case GLFW_KEY_F11: return ImGuiKey_F11;
            case GLFW_KEY_F12: return ImGuiKey_F12;
            default: return ImGuiKey_None;
        }
    }
    inline ImGuiKey ImGuiLayer::GetImGuiModForKeyCode(Saturn::KeyCode keycode)
    {
        switch ((int)keycode)
        {
            case GLFW_KEY_LEFT_CONTROL:
            case GLFW_KEY_RIGHT_CONTROL:
                return ImGuiKey_ModCtrl;
            case GLFW_KEY_LEFT_ALT:
            case GLFW_KEY_RIGHT_ALT:
                return ImGuiKey_ModAlt;
            case GLFW_KEY_LEFT_SHIFT:
            case GLFW_KEY_RIGHT_SHIFT:
                return ImGuiKey_ModShift;
            case GLFW_KEY_LEFT_SUPER:
            case GLFW_KEY_RIGHT_SUPER:
                return ImGuiKey_ModSuper;
            default:
                return ImGuiKey_None;
        }
    }

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent((int)e.GetMouseButton(), true);
		return true;
	}
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent((int)e.GetMouseButton(), false);
		return true;
	}
	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		return true;
	}
	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());
        if (io.WantCaptureMouse)
		    return true;
        return false;
	}
    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGuiLayer::GetImGuiKeyForKeyCode(e.GetKeyCode()), true);

        ImGuiKey modKey = ImGuiLayer::GetImGuiModForKeyCode(e.GetKeyCode());
        if (modKey != ImGuiKey_None)
            io.AddKeyEvent(modKey, true);
		return true;
	}
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGuiLayer::GetImGuiKeyForKeyCode(e.GetKeyCode()), false);

        ImGuiKey modKey = ImGuiLayer::GetImGuiModForKeyCode(e.GetKeyCode());
        if (modKey != ImGuiKey_None)
            io.AddKeyEvent(modKey, false);
		return true;
	}
    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(e.GetCharacter());
        if (io.WantTextInput)
            return true;
        return false;
    }
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return true;
	}
}
