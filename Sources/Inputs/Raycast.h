#pragma once

#include "Inputs.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Sources/Renderer/CameraController.h"

class CameraController;

class Raycast {

public: 
	static void Init(CameraController* cam);

public:

	static glm::vec3 RayCast_XZplane(const glm::vec3& plane_position);
	static glm::vec3 ShootRay(CameraController* camera);
	static void GetWorldPosition();

private:
	static Raycast* s_Instance;
	static CameraController* s_Camera;
};

