#pragma once
#include "Saturn/Rendering/Buffer.h"

namespace Saturn
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
		friend class VertexBuffer;
	protected:
		OpenGLVertexBuffer(float* vertices, UInt32 size);
	public:
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override final;
		virtual void Unbind() const override final;

		virtual void SetLayout(const BufferLayout& layout) override final;
		virtual const BufferLayout& GetLayout() const override final;
	private:
		UInt32 m_Id = 0;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
		friend class IndexBuffer;
	protected:
		OpenGLIndexBuffer(UInt32* indices, UInt32 size);
	public:
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override final;
		virtual void Unbind() const override final;

		virtual UInt32 GetCount() const override final;
	private:
		UInt32 m_Id;
		UInt32 m_Count;
	};
}