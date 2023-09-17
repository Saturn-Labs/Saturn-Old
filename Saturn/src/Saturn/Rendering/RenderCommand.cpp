#include "SaturnPch.h"
#include "Saturn/Rendering/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Saturn
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}