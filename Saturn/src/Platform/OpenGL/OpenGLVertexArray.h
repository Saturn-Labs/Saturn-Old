#pragma once
#include "Saturn/Rendering/VertexArray.h"

namespace Saturn
{
	class OpenGLVertexArray : public VertexArray
	{
		friend class VertexArray;
	protected:
		OpenGLVertexArray();
	
	public:
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override final;
		virtual void Unbind() const override final;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override final;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override final;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override final
		{
			return m_VertexBuffers;
		}

		virtual std::weak_ptr<IndexBuffer> GetIndexBuffer() const override final
		{
			return m_IndexBuffer;
		}
	private:
		UInt32 m_Id = 0;
		UInt32 m_IndexAttrib = 0;

		std::vector<Ref<VertexBuffer>> m_VertexBuffers = {};
		Ref<IndexBuffer> m_IndexBuffer = nullptr;
	};
}