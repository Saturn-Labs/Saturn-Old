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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override final;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override final;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override final
		{
			return m_VertexBuffers;
		}

		virtual std::weak_ptr<IndexBuffer> GetIndexBuffer() const override final
		{
			return m_IndexBuffer;
		}
	private:
		UInt32 m_Id = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers = {};
		std::shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;
	};
}