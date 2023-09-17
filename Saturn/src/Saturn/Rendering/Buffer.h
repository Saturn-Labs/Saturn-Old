#pragma once
#include "Saturn/Core.h"

namespace Saturn
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static UInt32 GetShaderDataTypeSize(ShaderDataType dataType)
	{
		switch (dataType)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Int:
				return 4;
			case ShaderDataType::Float2:
			case ShaderDataType::Int2:
				return 8;
			case ShaderDataType::Float3:
			case ShaderDataType::Int3:
				return 12;
			case ShaderDataType::Float4:
			case ShaderDataType::Int4:
				return 16;
			case ShaderDataType::Mat3:
				return 4 * 3 * 3;
			case ShaderDataType::Mat4:
				return 4 * 4 * 4;
			case ShaderDataType::Bool:
				return 1;
		}

		ST_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		UInt32 Offset;
		UInt32 Size;
		bool Normalized;

		BufferElement() { }

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Normalized(normalized), Size(GetShaderDataTypeSize(type)), Offset(0)
		{
		}

		UInt32 GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Int:
					return 1;
				case ShaderDataType::Float2:
				case ShaderDataType::Int2:
					return 2;
				case ShaderDataType::Float3:
				case ShaderDataType::Int3:
					return 3;
				case ShaderDataType::Float4:
				case ShaderDataType::Int4:
					return 4;
				case ShaderDataType::Mat3:
					return 3 * 3;
				case ShaderDataType::Mat4:
					return 4 * 4;
				case ShaderDataType::Bool:
					return 1;
			}

			ST_ASSERT(false, "Unknown shader data type!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() { }

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const
		{
			return m_Elements;
		}

		inline UInt32 GetStride() const
		{
			return m_Stride;
		}

		std::vector<BufferElement>::iterator begin()
		{
			return m_Elements.begin();
		}

		std::vector<BufferElement>::iterator end()
		{
			return m_Elements.end();
		}

		std::vector<BufferElement>::const_iterator begin() const
		{
			return m_Elements.begin();
		}

		std::vector<BufferElement>::const_iterator end() const
		{
			return m_Elements.end();
		}
	private:
		void CalculateOffsetsAndStride()
		{
			UInt32 offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		UInt32 m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer()
		{
		};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, UInt32 size, Int32 drawMode = 0x88E4);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer()
		{
		};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual UInt32 GetCount() const = 0;

		static Ref<IndexBuffer> Create(UInt32* indices, UInt32 count, Int32 drawMode = 0x88E4);
	};
}