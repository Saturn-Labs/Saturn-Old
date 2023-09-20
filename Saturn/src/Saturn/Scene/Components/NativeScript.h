#pragma once
#include "Saturn/Scene/Entity/Entity.h"
#include "Saturn/Scene/Behaviours/ScriptableBehaviour.h"

namespace Saturn::Component
{
	struct NativeScript
	{
		friend class Scene;

		Scoped<ScriptableBehaviour> Behaviour = nullptr;

		NativeScript() = default;
		NativeScript(const NativeScript&) = default;

		template<typename T>
		T& Bind(const Entity& entity)
		{
			Behaviour = CreateScoped<T>();
			Behaviour->m_Entity = entity;
			Behaviour->OnCreate();
			return (T&)*Behaviour;
		}

		void OnCreate()
		{
			if (Behaviour)
				Behaviour->OnCreate();
		}
		void OnUpdate(Time time)
		{
			if (Behaviour)
				Behaviour->OnUpdate(time);
		}
		void OnDestroy()
		{
			if (Behaviour)
				Behaviour->OnDestroy();
		}
	};
}