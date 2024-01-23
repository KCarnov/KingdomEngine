#include "Inputs.h"


Inputs* Inputs::s_Instance = new Inputs();

bool Inputs::IsKeyPressedImpl(int keycode)
{
	
	GLFWwindow* window = Application::Get().GetGLFWwindow();
	int state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;

}

bool Inputs::IsMouseButtonPressedImpl(int button)
{
	GLFWwindow* window = Application::Get().GetGLFWwindow();

	int state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

float Inputs::GetMouseXImpl()
{
	GLFWwindow* window = Application::Get().GetGLFWwindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return (float)xpos;
}

float Inputs::GetMouseYImpl()
{
	GLFWwindow* window = Application::Get().GetGLFWwindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return (float)ypos;
}

std::pair<float, float> Inputs::GetMousePosImpl()
{
	GLFWwindow* window = Application::Get().GetGLFWwindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return { (float)xpos, (float)ypos };
	//auto [x, y] = GetMousePos();
}
