#pragma once
#include "Saturn.h"

namespace Sandbox
{
	class Sandbox2DLayer : public Saturn::Layer
	{
	public:
		Sandbox2DLayer();
		virtual ~Sandbox2DLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Saturn::Time time) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Saturn::Event& event) override;

	private:
		Saturn::OrthoCameraController m_OrthoCameraController;
	
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_RadianRotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

		glm::vec4 m_Color = glm::vec4(1.0f);

		glm::vec3 m_LightPosition = glm::vec3(0.0f);
		glm::vec4 m_LightColor = glm::vec4(1.0f);

		Saturn::Ref<Saturn::Texture2D> m_Texture;

		bool m_ShowImGuiLayer = false;
		bool m_Attached = false;

		ImGuiIO* m_ImGuiIO = nullptr;
	};
}