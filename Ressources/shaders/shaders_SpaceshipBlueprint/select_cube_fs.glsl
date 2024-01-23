#version 450 core

out vec4 FragColor;

void main()
{
    vec3 BaseColor = vec3(0.9, 0.9, 0.1);
    FragColor = vec4(BaseColor,1.0f);
}