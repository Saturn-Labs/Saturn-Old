#pragma once
#include "glm/glm.hpp"
#include "Saturn/Rendering/VertexArray.h"
#include "Saturn/Common/Types.h"
#include "Saturn/Core/Core.h"
#include <memory>

namespace Saturn
{
	enum class DrawMode : int
	{
		Full = 0,
		Wireframe = 1,
		VertexPoint = 2,
	};

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL,
			Direct3D,
			Vulkan,
			Metal
		};

	public:
		virtual ~RendererAPI() = default;
		virtual void Initialize() = 0;
		virtual void SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height) = 0;
		virtual float GetTime() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void SetDrawMode(DrawMode mode) = 0;

		virtual void DrawIndexed(const VertexArray* vertexArray) = 0;
		virtual void DrawIndexed(const VertexArray* vertexArray, UInt32 count) = 0;

		inline static API GetRendererAPI()
		{
			return s_API;
		}

	private:
		static API s_API;
	};
}