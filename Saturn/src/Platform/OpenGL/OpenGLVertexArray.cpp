#include "saturnpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Saturn
{
	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Saturn::ShaderDataType::Float:
			case Saturn::ShaderDataType::Float2:
			case Saturn::ShaderDataType::Float3:
			case Saturn::ShaderDataType::Float4:
			case Saturn::ShaderDataType::Mat3:
			case Saturn::ShaderDataType::Mat4:
				return GL_FLOAT;
			case Saturn::ShaderDataType::Int:
			case Saturn::ShaderDataType::Int2:
			case Saturn::ShaderDataType::Int3:
			case Saturn::ShaderDataType::Int4:
				return GL_INT;
			case Saturn::ShaderDataType::Bool:
				return GL_BOOL;
		}

		ST_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_Id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_Id);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Saturn::Ref<VertexBuffer>& buffer)
	{
		ST_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "The VertexBuffer doesn't contain any layout!");
		
		glBindVertexArray(m_Id);
		buffer->Bind();

		UInt32 index = 0;
		const BufferLayout& layout = buffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Saturn::Ref<IndexBuffer>& buffer)
	{
		glBindVertexArray(m_Id);
		buffer->Bind();

		m_IndexBuffer = buffer;
	}
}