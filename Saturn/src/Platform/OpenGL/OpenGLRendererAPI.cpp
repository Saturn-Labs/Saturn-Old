#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Saturn
{
	void OpenGLRendererAPI::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
	{
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

	void OpenGLRendererAPI::DrawIndexed(const Saturn::Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer().lock()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}