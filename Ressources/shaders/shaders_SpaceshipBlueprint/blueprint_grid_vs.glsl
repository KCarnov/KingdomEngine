#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aVal;
layout (location = 2) in float aLevel;
layout (location = 3) in int aCubeIndex;
out int VertexID;
out float val;

void main()
{

    gl_Position = vec4(aPos + vec3(0.0,0.0,0.0), 1.0);
    VertexID = gl_VertexID;
    val = aVal;

}