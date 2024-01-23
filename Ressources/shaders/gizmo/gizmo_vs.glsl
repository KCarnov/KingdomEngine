#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 fColor;

uniform mat4 u_model;
uniform mat4 u_view_projection;

void main()
{
	gl_Position = u_view_projection * vec4(aPos, 1.0);
	fColor = aColor;
}