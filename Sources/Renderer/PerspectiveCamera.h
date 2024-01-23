#pragma once

#include <glm/glm.hpp>



class PerspectiveCamera
{
public:
	PerspectiveCamera(float left, float right, float bottom, float top);
	PerspectiveCamera(float zoom, float viewportWidth, float viewportHeight, float near , float far);


	void SetProjection(float left, float right, float bottom, float top);
	void SetProjection(float zoom, float viewportWidth, float viewportHeight, float near , float far);

	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

	float GetRotation() const { return m_Rotation; }
	void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GGetViewMatrix();
	const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	const void SetYawPitch(const float& yaw, const float& pitch);
	const glm::vec2& GetYawPitch() { return glm::vec2(Yaw, Pitch); };

	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;

private:
	void RecalculateViewMatrix();
private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;

	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

	glm::vec3 WorldUp = { 0.0f, 1.0f, 0.0f };
	// euler Angles
	float Yaw = 0.0f;
	float Pitch = -89.0f;

	float m_Rotation = 0.0f;
};


