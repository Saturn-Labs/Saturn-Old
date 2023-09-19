#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "glad/glad.h"

namespace Saturn
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, UInt32 size, Int32 drawMode)
	{
		ST_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, drawMode);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(UInt32 size, Int32 drawMode)
	{
		ST_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, drawMode);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ST_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	void OpenGLVertexBuffer::SetData(void* data, UInt32 size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	//====================================================================//

	OpenGLIndexBuffer::OpenGLIndexBuffer(UInt32* indices, UInt32 count, Int32 drawMode)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(UInt32), indices, drawMode);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	UInt32 OpenGLIndexBuffer::GetCount() const
	{
		return m_Count;
	}
}