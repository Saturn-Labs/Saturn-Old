#pragma once

namespace Saturn
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void InitializeContext() = 0;
		virtual void SwapBuffers() = 0;
	};
}