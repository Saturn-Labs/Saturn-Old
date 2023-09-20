#include "SceneHierarchy.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace Saturn
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		m_Context->m_Registry.each([&](auto entity)
		{
			Entity _entity = Entity{ entity, m_Context.get() };
			DrawEntityNode(_entity);	
		});

		if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(0))
		{
			m_SelectionContext = {};
		}

		//blank space
		if (ImGui::BeginPopupContextWindow("HierarchyCtxMenu", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				m_Context->CreateEntity("Empty Entity");
			}
			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties Inspector");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
			if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, 30)))
			{
				ImGui::OpenPopup("AddComponentPopup");
			}

			if (ImGui::BeginPopup("AddComponentPopup"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<Component::CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<Component::SpriteRenderer>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		Component::Tag& tag = entity.GetComponent<Component::Tag>();
		
		ImGuiTreeNodeFlags flags = (m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0) | 
			ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool expanded = ImGui::TreeNodeEx((const void*)(UInt64)(UInt32)entity, flags, tag.Name.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool deleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Remove Entity"))
			{
				deleted = true;
			}
			ImGui::EndPopup();
		}

		if (expanded)
		{
			ImGui::TreePop();
		}

		if (deleted)
		{
			m_Context->RemoveEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
			
	}

	static void DrawVec3Control(const std::string label,
		Vector3& vector, float resetValue = 0.0f,
		float collumnWidth = 100.0f, float speed = 0.1f, float min = 0.0f, float max = 0.0f, const char* format = "%.2f", const char* uuid = nullptr)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		if (!uuid)
			ImGui::PushID(label.c_str());
		else
			ImGui::PushID(uuid);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, collumnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize{ lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			vector.x = resetValue;
		ImGui::PopFont();
		ImGui::SameLine();
		ImGui::DragFloat("##X", &vector.x, speed, min, max, format);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			vector.y = resetValue;
		ImGui::PopFont();
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &vector.y, speed, min, max, format);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			vector.z = resetValue;
		ImGui::PopFont();
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &vector.z, speed, min, max, format);
		ImGui::PopItemWidth();
		ImGui::PopStyleColor(3);

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	template<typename T, typename UIFunc>
	static void DrawComponent(const std::string& label, Entity entity, const UIFunc& func)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | 
			ImGuiTreeNodeFlags_AllowItemOverlap | 
			ImGuiTreeNodeFlags_SpanAvailWidth |
			ImGuiTreeNodeFlags_Framed |
			ImGuiTreeNodeFlags_FramePadding;

		if (entity.HasComponent<T>())
		{
			T& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx(label.c_str(), treeNodeFlags);
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvail.x - lineHeight * 0.5f);
			if (ImGui::Button("-", ImVec2(lineHeight, lineHeight)))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				func(component);
				ImGui::TreePop();
				ImGui::Spacing();
				ImGui::Spacing();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		DrawComponent<Component::Tag>("Tag", entity, 
			[](Component::Tag& tag)
		{
			char bufferName[256];
			memset(bufferName, 0, sizeof(bufferName));
			strcpy(bufferName, tag.Name.c_str());

			if (ImGui::InputText("Name", bufferName, sizeof(bufferName)))
			{
				tag.Name = std::string(bufferName);
			}
		});
		DrawComponent<Component::Transform>("Transform", entity, 
			[](Component::Transform& transform)
		{
			static Vector3 radianRotation{};
			DrawVec3Control("Position", transform.Position, 0.0f, 100.0f, 0.075f, 0.0f, 0.0f, "%.2f", "MTRP");
			DrawVec3Control("Rotation", radianRotation, 0.0f, 100.0f, 0.15f, 0.0f, 0.0f, "%.2f", "MTRR");
			transform.Rotation = (radianRotation * 3.14159265359f / 180.0f); //% 360.0f;
			DrawVec3Control("Scale", transform.Scale, 1.0f, 100.0f, 0.15f, 0.0f, 0.0f, "%.2f", "MTRS");
		});
		DrawComponent<Component::CameraComponent>("Camera", entity,
			[](Component::CameraComponent& camera)
		{
			ImGui::Checkbox("Is Main Camera", &camera.Main);

			const char* projectionTypeS[] = { "Orthographic", "Perspective" };
			const char* currentProjection = projectionTypeS[(int)camera.Camera.GetCameraProjectionType()];
			if (ImGui::BeginCombo("Projection Type", currentProjection))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentProjection == projectionTypeS[i];
					if (ImGui::Selectable(projectionTypeS[i], isSelected))
					{
						currentProjection = projectionTypeS[i];
						camera.Camera.SetCameraProjectionType((CameraProjectionType)i);
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (camera.Camera.GetCameraProjectionType() == CameraProjectionType::Perspective)
			{
				float perspVFov = camera.Camera.GetPerspectiveVerticalFOV() / 3.14159265359f * 180.0f;
				if (ImGui::DragFloat("Field of View", &perspVFov, 0.25f, 20.0f, 120.0f))
				{
					camera.Camera.SetPerspectiveVerticalFOV(perspVFov * 3.14159265359f / 180.0f);
				}

				float nearClip = camera.Camera.GetPerspectiveNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip))
				{
					camera.Camera.SetPerspectiveNearClip(nearClip);
				}

				float farClip = camera.Camera.GetPerspectiveFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip))
				{
					camera.Camera.SetPerspectiveFarClip(farClip);
				}
			}
			if (camera.Camera.GetCameraProjectionType() == CameraProjectionType::Orthographic)
			{
				float orthoSize = camera.Camera.GetOrthoSize();
				if (ImGui::DragFloat("Orthographic Size", &orthoSize))
				{
					camera.Camera.SetOrthoSize(orthoSize);
				}

				float nearClip = camera.Camera.GetOrthoNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip))
				{
					camera.Camera.SetOrthoNearClip(nearClip);
				}

				float farClip = camera.Camera.GetOrthoFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip))
				{
					camera.Camera.SetOrthoFarClip(farClip);
				}

				ImGui::Checkbox("Fixed Aspect Ratio", &camera.FixedAspect);
			}
		});
		DrawComponent<Component::SpriteRenderer>("Sprite Renderer", entity,
			[](Component::SpriteRenderer& component)
		{
			ImGui::ColorEdit4("Color", &component.Color[0]);
		});
	}
}