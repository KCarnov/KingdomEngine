#pragma once
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sources/KingdomEngine.h"
#include "Misc/Gizmos.h"
#include "Renderer/Shader.h"
#include "Renderer/PerspectiveCamera.h"
#include "Renderer/CameraController.h"
#include "Renderer/Texture.h"
#include <entt/entt.hpp>
#include "Sources/Renderer/VertexArray.h"
#include "Sources/Renderer/Buffer.h"
#include "Sources/Renderer/RendererAPI.h"
#include "ImGui/ImGuiLayer.h"
#include "Sources/Inputs/Raycast.h"

#include "Sources/Terrain/TerrainGenerator.h"

#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"


class Texture;
class CameraController;
class MarchingCubes; // necessaire a cause de event ??


class GameLayer0 {


public:
	GameLayer0();
	~GameLayer0();

	entt::registry m_Registry;

	void OnCreate();
	void OnUpdate(const float& dT);
	void OnEvent(Event& e);

	void OnImGui();

private:
	std::shared_ptr<VertexArray>  m_VAOT;
	std::shared_ptr<VertexBuffer> m_VBOT;
	std::shared_ptr<IndexBuffer>  m_IBOT;
	std::shared_ptr<Shader> m_shaderT;

private:
	CameraController* camera;
	Texture* texT;
	Texture* texT2;
	TerrainGenerator* m_Terrain;


	std::shared_ptr<Gizmos>  m_gizmos;
private:
	unsigned int m_ViewportWidth;
	unsigned int m_ViewportHeight;
	bool m_POLYGON_MODE = false;
	void UpdateSystems();
	void RenderSystems();

	bool OnMouseClicked(MouseButtonPressedEvent& e);
	bool OnMouseReleased(MouseButtonReleasedEvent& e);
	bool OnKeyTyped(KeyTypedEvent& e);
	const char* Name = "Game Layer0";

	struct GameData {
		glm::mat4 data;
	};

	static std::unique_ptr<GameData> m_GameData;

	bool Show_Blueprint_Grid;

	struct display_opts {
		bool gizmo = true;
		bool basegrid = true;

		bool terrain = false;
	} m_display;

	glm::vec3 target = { 1.0f,0.0f,0.0f };
	void ImGui_vec3(const char* label, glm::vec3& v);

	bool DragStart = false;
	glm::vec2 DragFirst = { 0.0f,0.0f };
	glm::vec2 DragLast = { 0.0f,0.0f };




};