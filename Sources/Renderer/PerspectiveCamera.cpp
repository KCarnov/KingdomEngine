#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>



PerspectiveCamera::PerspectiveCamera(float left, float right, float bottom, float top)
	: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
{

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

PerspectiveCamera::PerspectiveCamera(float zoom, float viewportWidth, float viewportHeight, float near, float far)
	: m_ProjectionMatrix(glm::perspective(glm::radians(zoom), viewportWidth / viewportHeight, near, far)),
	m_ViewMatrix(1.0f), Front({0.0f,0.0f,-1.0f})
{

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PerspectiveCamera::SetProjection(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PerspectiveCamera::SetProjection(float zoom, float viewportWidth, float viewportHeight, float near, float far)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(zoom), viewportWidth / viewportHeight, near, far);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

const glm::mat4& PerspectiveCamera::GGetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + Front, Up);
}

const void PerspectiveCamera::SetYawPitch(const float& yaw, const float& pitch)
{
	Yaw = yaw;
	Pitch = pitch;

}

void PerspectiveCamera::RecalculateViewMatrix()
{
	// calculate the new Front vector
	glm::vec3 front(0.0f, 0.0f, 0.0f);
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));

	//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
	//	glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	m_ViewMatrix = GGetViewMatrix();
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

