#include "CameraController.h"

CameraController::CameraController(float w, float h, float zoom, float near, float far)
	:m_camera(zoom, w, h, near, far), m_zoom(zoom), m_AspectRatio(w/h), w(w), h(h), near(near), far(far)
{
}

void CameraController::OnUpdate(float ts)
{
	if (Inputs::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		m_CameraTranslationSpeed = m_CameraTranslationSpeedFast;
	}
	else
	{
		m_CameraTranslationSpeed = m_CameraTranslationSpeedSlow;
	}
	if (Inputs::IsKeyPressed(GLFW_KEY_W) == GLFW_PRESS)
		m_CameraPosition += m_camera.Front * m_CameraTranslationSpeed;
	if (Inputs::IsKeyPressed(GLFW_KEY_S) == GLFW_PRESS)
		m_CameraPosition -= m_camera.Front * m_CameraTranslationSpeed;
	if (Inputs::IsKeyPressed(GLFW_KEY_A) == GLFW_PRESS)
		m_CameraPosition -= m_camera.Right * m_CameraTranslationSpeed;
	if (Inputs::IsKeyPressed(GLFW_KEY_D) == GLFW_PRESS)
		m_CameraPosition += m_camera.Right * m_CameraTranslationSpeed;

	//if (Inputs::IsKeyPressed(GLFW_KEY_A))
	//{
	//	//m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	//m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.z -= m_CameraTranslationSpeed * ts;
	//}
	//else if (Inputs::IsKeyPressed(GLFW_KEY_D))
	//{
	//	//m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	//m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.z += m_CameraTranslationSpeed * ts;
	//}

	//if (Inputs::IsKeyPressed(GLFW_KEY_W))
	//{
	//	//m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	//m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.x += m_CameraTranslationSpeed * ts;
	//}
	//else if (Inputs::IsKeyPressed(GLFW_KEY_S))
	//{
	//	//m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	//m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
	//}

	if (false)//m_Rotation
	{
		if (Inputs::IsKeyPressed(GLFW_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Inputs::IsKeyPressed(GLFW_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_camera.SetRotation(m_CameraRotation);
	}

	m_camera.SetPosition(m_CameraPosition);

	//m_CameraTranslationSpeed = m_zoom;
}

void CameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&CameraController::OnMouseScrolled, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseMovedEvent>(std::bind(&CameraController::OnMouseMoved, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&CameraController::OnKeyPressed, this, std::placeholders::_1));

}

float CameraController::SetZoomLevel(float zoom)
{
	return 0.0f;
}

bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_zoom -= e.GetYOffset() * 0.25f;
	m_zoom = std::max(m_zoom, 0.25f);
	m_camera.SetProjection(m_zoom, w, h, near, far);
	return false;
}

bool CameraController::OnMouseMoved(MouseMovedEvent& e)
{

	float xpos = static_cast<float>(e.GetX());
	float ypos = static_cast<float>(e.GetY());

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (Inputs::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		Yaw += xoffset*m_CameraRotationSpeed;
		Pitch += yoffset*m_CameraRotationSpeed;

		if (Pitch > 89.9f)
			Pitch = 89.9f;
		if (Pitch < -89.9f)
			Pitch = -89.9f;

			m_camera.SetYawPitch(Yaw, Pitch);
	}


	return false;
}

bool CameraController::OnKeyPressed(KeyPressedEvent& e)
{

	return false;
}
