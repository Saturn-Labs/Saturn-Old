#include <Saturn.h>

#include "SandboxLayer.h"

class Sandbox : public Saturn::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}
	
	~Sandbox()
	{

	}
};

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}