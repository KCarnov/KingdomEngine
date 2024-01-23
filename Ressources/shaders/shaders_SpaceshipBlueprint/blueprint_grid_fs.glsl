#version 450 core
out vec4 FragColor;
in vec3 GridColor;

void main()
{
    FragColor = vec4(GridColor,1.0f);
}