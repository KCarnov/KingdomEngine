#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lib/stb/stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "ImGui/ImGuiLayer.h"

#include "Window/Window.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Sources/Renderer/RendererAPI.h"

#include "Inputs/Inputs.h"
#include "KingdomEngine.h"
#include "GameLayer.h"
#include "GameLayer0.h"

#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

class GameLayer;
class GameLayer0;

class Application {
	
public:
	Application();
	~Application();
	
	void Run();
	void OnEvent(Event& e);

	unsigned int GetWindowWidth() const;
	unsigned int GetWindowHeight() const;
private:
	bool OnMouseMoveEvent(MouseMovedEvent& e);
public:
	
	static Application& Get() { return *s_Instance; }
	GLFWwindow* GetGLFWwindow() { return m_GLFWwindow; }
	Window& GetWindow() { return *m_window; }
private:
	GameLayer* m_GameLayer;
	GameLayer0* m_GameLayer0;
	std::unique_ptr<Window> m_window;
	GLFWwindow* m_GLFWwindow;

	ImGuiLayer* ImGui;

private:
	bool m_Running = true;
	float lastFrame = 0;
	float deltaTime = 0;

	static Application* s_Instance;
};

