#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <functional>

#include "Sources/Events/Events.h"
#include "Sources/KingdomEngine.h"
#include "Sources/Events/MouseEvent.h"
#include "Sources/Events/KeyEvent.h"

struct WindowProperties {
	const char* Title;
	unsigned int Width;
	unsigned int Height;

	WindowProperties(const char* title = "TEST", 
				     unsigned int width = 1920,
					 unsigned int height = 1080)
		:Title(title), Width(width), Height(height) {}
};

class Window
{
public:
	using EventCallbackFcn = std::function<void(Event&)>;

	Window(const WindowProperties windowsproperties);
	~Window();

	void OnUpdate();
	unsigned int GetWidth()  const { return m_WindowData.Width;  };
	unsigned int GetHeight() const { return m_WindowData.Height; };
	GLFWwindow* GetGLFWWindow()  { return m_window; } 
	Window* GetWindow()      const { return m_Instance; }
	void SetEventCallback(const EventCallbackFcn& callback);

private:
	GLFWwindow* m_window;
	Window* m_Instance = this;
	void Init();
	void SetCallbacks();


	struct WindowData {
		unsigned int Width, Height;
		EventCallbackFcn EventCallback;
	};
	WindowData m_WindowData;


};

