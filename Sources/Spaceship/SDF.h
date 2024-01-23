#pragma once
#include "Sources/KingdomEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/integer.hpp>

#include "MCTable.h"

class SDF {
public:

	//typedef float (SDF::*func)(float, glm::ivec3, glm::ivec3);

	static float signed_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos);
	static float square_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos);
	static float circle_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos);
	static float trap_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos);
	static float rhombus_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos);
	static float H;
	static std::unique_ptr<SDF> s_Instance;
	static float ndot(const glm::vec2& a, const glm::vec2& b) { return a.x * b.x - a.y * b.y; }
private:

	static float dot2(const glm::vec2& x);
	static float length(const glm::vec3& v);
	static float length(const glm::vec2& v);

};