#pragma once

#pragma region Entry Point
#include "Saturn/EntryPoint.h"
#pragma endregion

#include <stdio.h>
#include "Saturn/Application.h"
#include "Saturn/Log.h"
#include "Saturn/Events/Event.h"
#include "Saturn/Events/EventType.h"
#include "Saturn/Events/EventCategory.h"
#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/ImGui/ImGuiLayer.h"
#include "Saturn/Layer.h"
#include "Saturn/Input.h"
#include "Saturn/MouseButton.h"
#include "Saturn/KeyCode.h"
#include "Saturn/Rendering/Buffer.h"
#include "Saturn/Rendering/OrthographicCamera.h"
#include "Saturn/Rendering/RenderCommand.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Rendering/Shader.h"
#include "Saturn/Shader/ShaderPreprocessor.h"
#include "Saturn/Rendering/Texture.h"
#include "Saturn/Rendering/Texture2D.h"
#include "Saturn/Rendering/VertexArray.h"
#include "Saturn/Core/Time.h"