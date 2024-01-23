#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct TransformComponent {

    glm::vec3 Value = glm::vec3(0.0f);
    glm::vec3 offset = glm::vec3(0.0f);
    int idx;
};