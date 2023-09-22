#pragma once
#include "Saturn/Core/Core.h"
#include "Saturn/Scene/Scene.h"
#include "Saturn/Scene/Entity/Entity.h"

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

namespace YAML
{
	template<>
	struct convert<Vector2>
	{
		static Node encode(const Vector2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}
		static bool decode(const Node& node, Vector2& rhs)
		{
			if (!node.IsSequence() || node.size() < 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};
	template<>
	struct convert<Vector3>
	{
		static Node encode(const Vector3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
		static bool decode(const Node& node, Vector3& rhs)
		{
			if (!node.IsSequence() || node.size() < 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
	template<>
 	struct convert<Vector4>
	{
		static Node encode(const Vector4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}
		static bool decode(const Node& node, Vector4& rhs)
		{
			if (!node.IsSequence() || node.size() < 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Saturn
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& sceneRef);

		template<typename T, typename SFunc>
		void SerializeComponent(Entity entity, SFunc func)
		{
			if (entity.HasComponent<T>())
				func(entity, entity.GetComponent<T>());
		}

		template<typename T, typename DSFunc>
		void DeserializeComponent(Entity entity, DSFunc func)
		{
			func(entity, entity.GetOrAddComponent<T>());
		}
		void SerializeEntity(YAML::Emitter& out, Entity entity);

		void Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);
	private:
		Ref<Scene> m_Scene;
	};
}