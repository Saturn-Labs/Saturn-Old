#pragma once

#include <stdio.h>

#include "Saturn/Scene/Scene.h"
#include "Saturn/Scene/Components/SpriteRenderer.h"
#include "Saturn/Scene/Components/Transform.h"
#include "Saturn/Scene/Components/Tag.h"
#include "Saturn/Scene/Components/CameraComponent.h"
#include "Saturn/Scene/Entity/Entity.h"

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
#include "Saturn/Rendering/Tilemap2D.h"
#include "Saturn/Rendering/Tile2D.h"
#include "Saturn/Rendering/Framebuffer.h"

#include "Saturn/Camera/Camera.h"
#include "Saturn/Camera/SceneCamera.h"

#include "Saturn/Shader/Shader.h"
#include "Saturn/Shader/ShaderLib.h"
#include "Saturn/Shader/ShaderProcessor.h"

#include "Saturn/Core/Application.h"
#include "Saturn/Core/Time.h"

#include "Saturn/IO/Log.h"
#include "Saturn/Main/Layer.h"
#include "Saturn/Main/LayerStack.h"
#include "Saturn/ImGui/ImGuiLayer.h"

#include "Saturn/Rendering/TransformationMatrix.h"
#include "Saturn/Rendering/SubTexture2D.h"

#include <imgui.h>