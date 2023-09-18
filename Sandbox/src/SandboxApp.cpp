#include <Saturn.h>

#include "Layers/SandboxLayer.h"
#include "Layers/Sandbox2DLayer.h"

class SandboxApp : public Saturn::Application
{
public:
	SandboxApp()
	{
		PushLayer(new Sandbox::Sandbox2DLayer());
	}
	
	~SandboxApp()
	{

	}
};

Saturn::Application* Saturn::CreateApplication()
{
	return new SandboxApp();
}