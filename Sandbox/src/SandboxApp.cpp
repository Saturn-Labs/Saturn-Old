#include <Saturn.h>

class TestLayer : public Saturn::Layer
{
public:
	TestLayer() : Layer("Test Layer") { }

	void OnUpdate() override
	{
		ST_INFO("ExampleLayer updating!");
	}

	void OnEvent(Saturn::Event& e) override
	{
		ST_INFO("ExampleLayer {0}", e.ToString());
	}
};

class Sandbox : public Saturn::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}
	
	~Sandbox()
	{

	}
};

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}