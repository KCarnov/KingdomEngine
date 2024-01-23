#pragma once

#include "PerspectiveCamera.h"
#include "Sources/Inputs/Inputs.h"
#include "Sources/Events/MouseEvent.h"
#include "Sources/Events/KeyEvent.h"

class CameraController {

public:
	CameraController(float w, float h, float zoom, float near, float far);

	void OnUpdate(float ts);
	void OnEvent(Event& e);

	PerspectiveCamera& GetCamera() { return m_camera; }
	float GetZoomLevel() { return m_zoom; }
	float SetZoomLevel(float zoom);

	float GetViewportWidth() { return w; }
	float GetViewportHeight() { return h; }

private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnMouseMoved(MouseMovedEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);
private:

	float m_AspectRatio;
	float w = 0.0f, h = 0.0f;
	float near = 0.0f, far = 0.0f;
	float m_zoom = 1.0f;
	PerspectiveCamera m_camera;

	glm::vec3 m_CameraPosition = { 4.0f, 50.0f, 1.0f };
	float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
	float m_CameraTranslationSpeed = 0.2f, m_CameraRotationSpeed = 0.5f;
	float m_CameraTranslationSpeedSlow = 0.2f, m_CameraTranslationSpeedFast = 2.5f;
	// euler Angles
	float Yaw = 0.0f;
	float Pitch = -89.0f;
	bool firstMouse = true;
	float lastX = 0.0f;
	float lastY = 0.0f;
};