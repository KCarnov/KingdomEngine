#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in float aLevel;

uniform mat4 u_model;
uniform mat4 u_view_projection;
uniform ivec2 u_grid;

out VS_OUT {
    vec3 normal;
    float level;
} vs_out;  

void main()
{
    
    gl_Position = vec4(aPos + vec3(0.0,0.0,0.0), 1.0);
	vs_out.normal = aNormal;
    vs_out.level = aLevel;

}