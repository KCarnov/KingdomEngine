#version 450 core

uniform mat4 u_model;
uniform mat4 u_view_projection;

void main()
{
	gl_Position = vec4(vec3(0.0), 1.0);
}