#include "saturnpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Saturn
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ST_CORE_ASSERT(windowHandle, "Window handle doesnt exists!");

		
	}

	void OpenGLContext::InitializeContext()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ST_CORE_ASSERT(status, "Failure on trying to initialize \"Glad\".");
		ST_CORE_TRACE("OpenGL Renderer: {0}", (const char*)glGetString(GL_VERSION));
		ST_CORE_TRACE("Graphics Processor: {0}", (const char*)glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers() 
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}