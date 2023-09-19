#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Saturn
{
	void OpenGLRendererAPI::Initialize()
	{
		ST_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void OpenGLRendererAPI::SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
	{
		ST_PROFILE_FUNCTION();

		glViewport((int)x, (int)y, (int)width, (int)height);
	}

	float OpenGLRendererAPI::GetTime()
	{
		return (float)glfwGetTime();
	}
	 
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetDrawMode(DrawMode mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, (mode == DrawMode::Full ? GL_FILL : (mode == DrawMode::Wireframe ? GL_LINE : GL_POINT)));
	}

	void OpenGLRendererAPI::DrawIndexed(const VertexArray* vertexArray)
	{
		ST_PROFILE_FUNCTION();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer().lock().get()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawIndexed(const VertexArray* vertexArray, UInt32 count)
	{
		ST_PROFILE_FUNCTION();

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}