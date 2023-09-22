#include "SaturnPch.h"
#include "SceneSerializer.h"

namespace Saturn
{
	SceneSerializer::SceneSerializer(const Ref<Scene>& sceneRef)
		: m_Scene(sceneRef)
	{
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;
		{ //entity map
			out << YAML::Key << "Entity" << YAML::Value << "327467404365487"; //TODO: use valid UUID

			SceneSerializer::SerializeComponent<Component::Tag>(entity,
				[&out](Entity entity, Component::Tag& tag)
			{
				out << YAML::Key << "Component::Tag";
				out << YAML::BeginMap;
				{ //Component::Tag
					out << YAML::Key << "Name" << YAML::Value << tag.Name;
					out << YAML::EndMap;
				}
			});

			SceneSerializer::SerializeComponent<Component::Transform>(entity,
				[&out](Entity entity, Component::Transform& transform)
			{
				out << YAML::Key << "Component::Transform";
				out << YAML::BeginMap;
				{ //Component::Transform
					out << YAML::Key << "Position" << YAML::Value << transform.GetTranslation();
					out << YAML::Key << "Rotation" << YAML::Value << transform.GetEulerAngles();
					out << YAML::Key << "Scale" << YAML::Value << transform.GetScale();
					out << YAML::EndMap;
				}
			});

			SceneSerializer::SerializeComponent<Component::CameraComponent>(entity,
				[&out](Entity entity, Component::CameraComponent& camera)
			{
				out << YAML::Key << "Component::CameraComponent";
				out << YAML::BeginMap;
				{ //Component::CameraComponent
					out << YAML::Key << "Camera";
					out << YAML::BeginMap;
					{ //Camera
						out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.Camera.GetCameraProjectionType();
						out << YAML::Key << "FieldOfView" << YAML::Value << camera.Camera.GetPerspectiveVerticalFOV();
						out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.Camera.GetPerspectiveNearClip();
						out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.Camera.GetPerspectiveFarClip();
						out << YAML::Key << "OrthoSize" << YAML::Value << camera.Camera.GetOrthoSize();
						out << YAML::Key << "OrthoNear" << YAML::Value << camera.Camera.GetOrthoNearClip();
						out << YAML::Key << "OrthoFar" << YAML::Value << camera.Camera.GetOrthoFarClip();
						out << YAML::EndMap;
					}
					out << YAML::Key << "IsMain" << YAML::Value << camera.Main;
					out << YAML::Key << "FixedAspectRatio" << YAML::Value << camera.FixedAspect;
					out << YAML::EndMap;
				}
			});

			SceneSerializer::SerializeComponent<Component::SpriteRenderer>(entity,
				[&out](Entity entity, Component::SpriteRenderer& spriteRenderer)
			{
				out << YAML::Key << "Component::SpriteRenderer";
				out << YAML::BeginMap;
				{ //Component::SpriteRenderer
					out << YAML::Key << "Color" << YAML::Value << spriteRenderer.Color;
					out << YAML::EndMap;
				}
			});

			out << YAML::EndMap;
		}
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		{
			out << YAML::Key << "Scene" << YAML::Value << "Untitled";
			out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
			{
				m_Scene->m_Registry.each([&](auto enttId)
				{
					Entity entity = { enttId, m_Scene.get() };
					if (!entity)
						return;
					SerializeEntity(out, entity);
				});
				out << YAML::EndSeq;
			}
			out << YAML::EndMap;
		}

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entityNode : entities)
			{
				UInt64 uuid = entityNode["Entity"].as<UInt64>(); //TODO: Use Valid UUIDS

				std::string name;
				auto tagCmp = entityNode["Component::Tag"];
				if (tagCmp)
					name = tagCmp["Name"].as<std::string>();

				Entity deserializedEntity = m_Scene->CreateEntity(name);
				
				//Component::Transform
				{
					auto node = entityNode["Component::Transform"];
					if (node)
					{
						auto& transform = deserializedEntity.GetOrAddComponent<Component::Transform>();
						transform.SetTranslation(node["Position"].as<Vector3>());
						transform.SetEulerAngles(node["Rotation"].as<Vector3>());
						transform.SetScale(node["Scale"].as<Vector3>());
					}
				}

				//Component::CameraComponent
				{
					auto node = entityNode["Component::CameraComponent"];
					if (node)
					{
						auto& camera = deserializedEntity.GetOrAddComponent<Component::CameraComponent>();
						camera.Main = node["IsMain"].as<bool>();
						camera.FixedAspect = node["FixedAspectRatio"].as<bool>();

						auto cameraNode = node["Camera"];
						if (cameraNode)
						{
							camera.Camera.SetCameraProjectionType((CameraProjectionType)cameraNode["ProjectionType"].as<int>());
							camera.Camera.SetPerspectiveVerticalFOV(cameraNode["FieldOfView"].as<float>());
							camera.Camera.SetPerspectiveNearClip(cameraNode["PerspectiveNear"].as<float>());
							camera.Camera.SetPerspectiveFarClip(cameraNode["PerspectiveFar"].as<float>());
							camera.Camera.SetOrthoSize(cameraNode["OrthoSize"].as<float>());
							camera.Camera.SetOrthoNearClip(cameraNode["OrthoNear"].as<float>());
							camera.Camera.SetOrthoFarClip(cameraNode["OrthoFar"].as<float>());
						}
					}
				}

				//Component::SpriteRenderer
				{
					auto node = entityNode["Component::SpriteRenderer"];
					if (node)
					{
						auto& spriteRenderer = deserializedEntity.GetOrAddComponent<Component::SpriteRenderer>();
						spriteRenderer.Color = node["Color"].as<Color>();
					}
				}
			}
		}
		return true;
	}
}