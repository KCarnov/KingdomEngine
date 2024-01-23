#version 450 core
layout (points) in;
layout (line_strip, max_vertices = 256) out;

uniform mat4 u_view_projection;
const float n = 30;
const float dxz = 4.0f;

void EmitLine(float x)
{
    gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(vec3(x,0.0,n*dxz),0.0));
    EmitVertex();
    gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(vec3(x,0.0,-n*dxz),0.0));
    EmitVertex();
    EndPrimitive();

    gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(vec3(n*dxz,0.0,x),0.0));
    EmitVertex();
    gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(vec3(-n*dxz,0.0,x),0.0));
    EmitVertex();
    EndPrimitive();
}

void main() {    
    for(float i=-n;i<=n;i++)
        EmitLine(i*dxz);
}  