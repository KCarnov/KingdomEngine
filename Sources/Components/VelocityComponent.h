#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct VelocityComponent {

    glm::vec3 Value;
    float norm;
    int idx;
};