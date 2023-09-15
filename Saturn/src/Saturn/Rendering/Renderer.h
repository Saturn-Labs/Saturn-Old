#pragma once

namespace Saturn
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL,
		Direct3D,
		Vulkan,
		Metal
	};

	class Renderer
	{
		static RendererAPI s_RendererAPI;
	public:
		inline static RendererAPI GetRendererAPI()
		{
			return s_RendererAPI;
		}
	};
}