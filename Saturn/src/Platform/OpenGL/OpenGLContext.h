#pragma once
#include "Saturn/Rendering/GraphicsContext.h"

struct GLFWwindow;

namespace Saturn
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void InitializeContext() override final;
		virtual void SwapBuffers() override final;
	private:
		GLFWwindow* m_WindowHandle;
	};
}