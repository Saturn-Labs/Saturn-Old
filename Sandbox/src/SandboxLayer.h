#pragma once
#include "Saturn/Layer.h"
#include "Saturn/Rendering/Shader.h"
#include "Saturn/Rendering/Buffer.h"
#include "Saturn/Rendering/VertexArray.h"
#include "Saturn/Rendering/OrthographicCamera.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Input.h"
#include "Saturn/Core/Time.h"
#include "Saturn/CGO/Transform.h"
#include "Saturn/Core.h"
#include "Saturn/Rendering/Texture2D.h"
#include "Saturn/Rendering/ShaderLib.h"

#include <memory>

class SandboxLayer : public Saturn::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(Saturn::Time time);
	virtual void OnImGuiRender();
	virtual void OnEvent(Saturn::Event& event);

private:
	Saturn::ShaderLibrary m_ShaderLibrary;

	Saturn::Ref<Saturn::VertexArray> m_VertexArray = nullptr;
	Saturn::Ref<Saturn::VertexBuffer> m_VertexBuffer = nullptr;
	Saturn::Ref<Saturn::IndexBuffer> m_IndexBuffer = nullptr;
	Saturn::Ref<Saturn::Texture2D> m_Texture = nullptr;

	Saturn::OrthographicCamera m_Camera;

	glm::vec3 m_Position = glm::vec3();
	glm::vec3 m_Rotation = glm::vec3();
	glm::vec3 m_Scale = glm::vec3(1.0f);
	glm::vec4 m_Color = glm::vec4(1.0f);
};