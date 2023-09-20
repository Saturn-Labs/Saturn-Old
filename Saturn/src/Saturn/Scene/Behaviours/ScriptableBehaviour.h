#pragma once
#include "Saturn/Core/Time.h"

namespace Saturn::Component
{
	struct NativeScript;
}

namespace Saturn
{
	class ScriptableBehaviour
	{
		friend class Scene;
		friend struct Component::NativeScript;
	public:

		virtual ~ScriptableBehaviour() = default;
	protected:
		virtual void OnCreate()
		{
		};

		virtual void OnUpdate(Time time)
		{
		}

		virtual void OnDestroy()
		{
		}

	public:
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	private:
		Entity m_Entity;
	};
}