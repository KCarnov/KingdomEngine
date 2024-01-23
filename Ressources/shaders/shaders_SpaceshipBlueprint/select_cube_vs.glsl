#version 450 core

uniform mat4 u_model;
uniform mat4 u_view_projection;
uniform vec3 u_pos;


void main()
{
    gl_Position = vec4(u_pos, 1.0);
}