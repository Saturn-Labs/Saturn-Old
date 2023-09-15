#pragma once

#include "Buffer.h"

namespace Saturn
{
	class VertexArray
	{
	public:
		virtual ~VertexArray()
		{
		};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual std::weak_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}