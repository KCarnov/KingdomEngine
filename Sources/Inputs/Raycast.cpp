#include "Raycast.h"

Raycast* Raycast::s_Instance = new Raycast();
CameraController* Raycast::s_Camera = nullptr;

void Raycast::Init(CameraController* cam)
{
	s_Camera = cam;
}

glm::vec3 Raycast::RayCast_XZplane(const glm::vec3& plane_position)
{
	
	glm::vec3 campos = s_Camera->GetCamera().GetPosition();
	float x = (2.0f * Inputs::GetMouseX()) / (float)s_Camera->GetViewportWidth() - 1.0f;
	float y = 1.0f - (2.0f * Inputs::GetMouseY()) / (float)s_Camera->GetViewportHeight();

	glm::vec4 ray_clip = glm::vec4(x, y, -1.0, 1.0);

	glm::vec4 ray_eye = glm::inverse(s_Camera->GetCamera().GetProjectionMatrix()) * ray_clip;
	ray_eye = glm::vec4{ ray_eye.x, ray_eye.y, -1.0f, 0.0f };
	glm::vec4 ray_wor = glm::normalize(glm::inverse(s_Camera->GetCamera().GetViewMatrix()) * ray_eye);

	glm::vec3 ray = glm::vec3{ ray_wor.x,ray_wor.y,ray_wor.z };

	//// t = (p0 - l0).n / (l.n)
	//// p0 : plane_position
	//// l0 : ray origin
	//// l : ray direction

	//// p = l0 + l*t;

	float t = 0.0f;
	if(glm::abs(ray.y) > 0.0)
		t = ((plane_position - campos).y) / ray.y;

	glm::vec3 p = campos + ray * t;
	return p;
}

glm::vec3 Raycast::ShootRay(CameraController* camera)
{

	glm::vec3 campos = camera->GetCamera().GetPosition();
	float x = (2.0f * Inputs::GetMouseX()) / (float)camera->GetViewportWidth() - 1.0f;
	float y = 1.0f - (2.0f * Inputs::GetMouseY()) / (float)camera->GetViewportHeight();

	glm::vec4 ray_clip = glm::vec4(x, y, -1.0, 1.0);

	glm::vec4 ray_eye = glm::inverse(camera->GetCamera().GetProjectionMatrix()) * ray_clip;
	ray_eye = glm::vec4{ ray_eye.x, ray_eye.y, -1.0f, 0.0f };
	glm::vec4 ray_wor = glm::normalize(glm::inverse(camera->GetCamera().GetViewMatrix()) * ray_eye);

	glm::vec3 ray = glm::vec3{ ray_wor.x,ray_wor.y,ray_wor.z };


	glm::vec3 n = { 0.0f,1.0f,0.0f }; //TODO : harcoded to flat terrain, have to change
	float d = 0.5f;

	glm::vec3 res = campos -( (glm::dot(n, campos) + d) / glm::dot(n, ray) * ray);

	return res;
}

void Raycast::GetWorldPosition()
{
}



//MouseX = Inputs::GetMouseX();
//MouseY = Inputs::GetMouseY();
//glm::vec3 campos = camera->GetCamera().GetPosition();
//float x = (2.0f * MouseX) / (float)m_ViewportWidth - 1.0f;
//float y = 1.0f - (2.0f * MouseY) / (float)m_ViewportHeight;
//float z = 1.0f;
//ray_nds = glm::vec3(x, y, z);
//
//glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
//
//ray_eye = glm::inverse(camera->GetCamera().GetProjectionMatrix()) * ray_clip;
//ray_eye = glm::vec4{ ray_eye.x, ray_eye.y, -1.0f, 0.0f };
//glm::vec4 ray_wor = glm::normalize(glm::inverse(camera->GetCamera().GetViewMatrix()) * ray_eye);
//
//
//ray = glm::vec3{ ray_wor.x,ray_wor.y,ray_wor.z };
//
//
//glm::vec3 n = { 0.0f,1.0f,0.0f };
//float d = 0.5f;
//t = -(glm::dot(n, campos) + d) / glm::dot(n, ray);
//
//res = campos + t * ray;