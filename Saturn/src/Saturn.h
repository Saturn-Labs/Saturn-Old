#pragma once

#include <stdio.h>

#include "Saturn/Events/Event.h"
#include "Saturn/Events/EventType.h"
#include "Saturn/Events/EventCategory.h"
#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Events/MouseEvent.h"

#include "Saturn/Input/Input.h"
#include "Saturn/Input/MouseButton.h"
#include "Saturn/Input/KeyCode.h"

#include "Saturn/Rendering/RenderCommand.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Rendering/Texture.h"
#include "Saturn/Rendering/Texture2D.h"
#include "Saturn/Rendering/VertexArray.h"
#include "Saturn/Rendering/Buffer.h"
#include "Saturn/Rendering/Renderer2D.h"

#include "Saturn/Camera/Controllers/OrthoCameraController.h"
#include "Saturn/Camera/OrthoCamera.h"

#include "Saturn/Shader/Shader.h"
#include "Saturn/Shader/ShaderLib.h"
#include "Saturn/Shader/ShaderPreprocessor.h"

#include "Saturn/Core/Application.h"
#include "Saturn/Core/Time.h"

#include "Saturn/IO/Log.h"
#include "Saturn/Main/Layer.h"
#include "Saturn/Main/LayerStack.h"
#include "Saturn/ImGui/ImGuiLayer.h"

#include "Saturn/Rendering/TransformationMatrix.h"

#include <imgui.h>