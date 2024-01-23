#pragma once
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sources/KingdomEngine.h"
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

#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
class Texture;
class CameraController;

class GameLayer {


public:
	GameLayer();
	~GameLayer();

	entt::registry m_Registry;

	void OnCreate();
	void OnUpdate(const float& dT);
	void OnEvent(Event& e);

	void OnImGui();

private:
	CameraController* camera;
	Texture* tex;
	Texture* texT;

	const int N = 1;
	glm::vec3* cubepos;
	glm::vec3* cubepos_ini;
	float* vel;

	glm::vec3* terrain;

	

	//GLuint VAO, VBO, IBO;
	unsigned int* m_indices;

private:
	unsigned int m_ViewportWidth;
	unsigned int m_ViewportHeight;
	bool m_POLYGON_MODE = false;
	void UpdateSystems();
	void RenderSystems();

	bool OnMouseClicked(MouseButtonPressedEvent& e);
	bool OnMouseReleased(MouseButtonReleasedEvent& e);
	bool OnKeyTyped(KeyTypedEvent& e);
	const char* Name = "Game Layer";
	glm::vec3 GetGridPosFromIndex(const unsigned int& index, const unsigned int& N);
	std::shared_ptr<VertexArray>  m_VAOT;
	std::shared_ptr<VertexBuffer> m_VBOT;
	std::shared_ptr<IndexBuffer>  m_IBOT;
	std::shared_ptr<Shader> myshaderT;

	std::shared_ptr<VertexArray>  m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<IndexBuffer>  m_IBO;
	std::shared_ptr<VertexBuffer> instancedVBO;
	std::shared_ptr<Shader> myshader;
	void CreateTerrain();

	struct GameData {
		glm::mat4 data;
	};

	static std::unique_ptr<GameData> m_GameData;

	glm::vec3 target = { 1.0f,0.0f,0.0f };
	void ImGui_vec3(const char* label, glm::vec3& v);

	bool DragStart = false;
	glm::vec2 DragFirst = { 0.0f,0.0f };
	glm::vec2 DragLast = { 0.0f,0.0f };

	/*Terrain* m_terrain;*/
};