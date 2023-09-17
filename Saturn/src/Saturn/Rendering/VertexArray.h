#pragma once
#include "Saturn/Core.h"
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
	
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual std::weak_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}