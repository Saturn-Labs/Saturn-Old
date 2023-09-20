#include <Saturn.h>

#include "EditorLayer.h"

namespace Saturn
{
	class SaturnEditorApp : public Application
	{
	public:
		SaturnEditorApp() : Application("Saturn Editor Runtime")
		{
			PushLayer(new EditorLayer());
		}

		~SaturnEditorApp()
		{

		}
	};

	Saturn::Application* Saturn::CreateApplication()
	{
		return new SaturnEditorApp();
	}
}