#include "SDF.h"

std::unique_ptr<SDF> SDF::s_Instance = std::make_unique<SDF>();

float SDF::signed_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos)
{
	return 0.0f;
}

float SDF::square_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos)
{

    //if (gridpoint.y == pos.y)
    //    return glm::max(glm::abs(gridpoint.x - pos.x), glm::abs(gridpoint.z - pos.z)) - size;
    //else
    //    return 0.8f;
    
    
    glm::vec3 p = gridpoint - pos;
    glm::vec3 q = abs(p) - glm::vec3(size, 0.5f, size);
    return length(glm::max(q, glm::vec3(0))) + glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f);


}
// https://www.shadertoy.com/view/Xds3zN
// Capped Cone - exact (https://iquilezles.org/articles/distfunctions/)
float SDF::circle_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos)
{
    glm::vec3 p = gridpoint - pos;
    glm::vec2 d = glm::abs(glm::vec2(length(glm::vec3(p.x,0.0,p.z)),p.y)) - glm::vec2(size,0.5f);

    return glm::min(glm::max(d.x, d.y), 0.0f) + length(glm::max(d, 0.0f));

	//return (glm::sqrt((gridpoint.x - pos.x) * (gridpoint.x - pos.x) + 
	//				  (gridpoint.z - pos.z) * (gridpoint.z - pos.z)) - size);

}

float SDF::trap_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos)
{
    float r1;
    float r2;
    float height;

    height = size;
    r1 = (size/2.0f);
    r2 = (size/4.0f);


    glm::vec2 p = (glm::vec2(gridpoint.x, gridpoint.z) - glm::vec2(pos.x, pos.z));
    glm::vec2 k1 = glm::vec2(r2, height);
    glm::vec2 k2 = glm::vec2(r2 - r1, 2.0 * height);
    p.x = abs(p.x);
    glm::vec2 ca = glm::vec2(p.x - glm::min((float)p.x, ((p.y < 0.0) ? r1 : r2)), abs(p.y) - height);
    glm::vec2 cb = p - k1 + k2 * glm::clamp(glm::dot(k1 - p, k2) / dot2(k2), 0.0f, 1.0f);
    float s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
    float d = s * glm::sqrt(glm::min(dot2(ca), dot2(cb)));


    glm::vec2 w = glm::vec2(d, glm::abs(gridpoint.y - pos.y) - 0.5f);
    return glm::min(glm::max(w.x, w.y), 0.0f) + length(glm::max(w, 0.0f));


}

// la,lb=semi axis, h=height, ra=corner
float SDF::rhombus_fcn(const float& size, const glm::ivec3& gridpoint, const glm::ivec3& pos)
{
    glm::vec3 p = gridpoint - pos;
    p = abs(p);
    float la = size;
    float lb = size / 2;
    float h = 0.25f;
    float ra = 0.0f;
    //float tmp = p.y;
    //p.y = p.z;
    //p.z = tmp;
    glm::vec2 b = glm::vec2(la, lb);
    float f = glm::clamp((SDF::ndot(b, b - 2.0f * glm::vec2(p.x, p.z))) / dot(b, b), -1.0f, 1.0f);
    glm::vec2 q = glm::vec2(length(glm::vec2(p.x, p.z) - 0.5f * b * glm::vec2(1.0f - f, 1.0f + f)) * glm::sign(p.x * b.y + p.z * b.x - b.x * b.y) - ra, p.y - 0.5f);
    return glm::min(glm::max(q.x, q.y), 0.0f) + length(max(q, 0.0f));
}


float SDF::dot2(const glm::vec2& x)
{
    return glm::dot(x, x);
}

float SDF::length(const glm::vec3& v)
{
    return glm::sqrt(glm::dot(v,v));
}

float SDF::length(const glm::vec2& v)
{
    return glm::sqrt(glm::dot(v, v));
}
//
//float opExtrusion(in vec3 p, in sdf2d primitive, in float h)
//{
//    float d = primitive(p.xy)
//        vec2 w = vec2(d, abs(p.z) - h);
//    return min(max(w.x, w.y), 0.0) + length(max(w, 0.0));
//}