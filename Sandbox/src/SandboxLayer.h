#pragma once
#include "Saturn/Layer.h"
#include "Saturn/Rendering/Shader.h"
#include "Saturn/Rendering/Buffer.h"
#include "Saturn/Rendering/VertexArray.h"
#include "Saturn/Rendering/OrthographicCamera.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Input.h"

#include <memory>

class SandboxLayer : public Saturn::Layer
{
public:
	std::shared_ptr<Saturn::Shader> m_BasicShader = nullptr;
	std::shared_ptr<Saturn::VertexArray> m_VertexArray = nullptr;
	std::shared_ptr<Saturn::VertexBuffer> m_VertexBuffer = nullptr;
	std::shared_ptr<Saturn::IndexBuffer> m_IndexBuffer = nullptr;

	Saturn::OrthographicCamera m_Camera;

	float x = 0;
	float xsin = 0;
	float xdegInc = 0.03f;
	float xdeg = 0;

	float y = 0;
	float ysin = 0;
	float ydegInc = 0.07f;
	float ydeg = 0;

	float rotZ = 0;
	float rotZInc = 0.95f;

	SandboxLayer();
	virtual ~SandboxLayer();
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate();
	virtual void OnImGuiRender();
	virtual void OnEvent(Saturn::Event& event);
};