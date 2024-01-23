#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

layout (location = 3) in vec3 instanced_Pos;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 u_model;
uniform mat4 u_view_projection;

void main()
{
	gl_Position = u_view_projection * vec4(aPos + instanced_Pos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	ourColor = aColor;
}