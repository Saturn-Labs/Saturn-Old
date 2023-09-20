#include "SaturnPch.h"
#include "Entity.h"

namespace Saturn
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_SceneReference(scene)
	{
	}
}
