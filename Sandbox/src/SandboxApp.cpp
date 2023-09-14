#include <Saturn.h>

class Sandbox : public Saturn::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Saturn::ImGuiLayer());
	}
	
	~Sandbox()
	{

	}
};

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}