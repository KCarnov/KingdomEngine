#version 450 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

uniform mat4  u_view_projection;
uniform float u_show_level;
uniform int   u_vertices_per_level;

in VS_OUT {
    vec3 normal;
    float level;
} gs_in[];  

out GS_OUT {
    vec3 normal;
    vec3 basecolor;
    vec4 texCoord;
} gs_out;  

void main() {    

    bool show = true;
    
    if((gs_in[0].level > u_show_level+1)) 
        show = false;

    if(show) 
    {
        float s = 0.0;
        gl_Position = u_view_projection * gl_in[0].gl_Position + vec4(vec3(0.0,0.0,s),0.0);
        gs_out.normal = gs_in[0].normal;
        gs_out.basecolor = vec3(gs_in[0].level,gs_in[1].level,gs_in[2].level)/6.0;
        gs_out.texCoord =  gl_in[0].gl_Position;
        EmitVertex();

        gl_Position = u_view_projection * gl_in[1].gl_Position + vec4(vec3(0.0,0.0,s),0.0);
        gs_out.normal = gs_in[1].normal;
        gs_out.basecolor = vec3(gs_in[0].level,gs_in[1].level,gs_in[2].level)/6.0;
        gs_out.texCoord =  gl_in[1].gl_Position;
        EmitVertex();

        gl_Position = u_view_projection * gl_in[2].gl_Position + vec4(vec3(0.0,0.0,s),0.0);
        gs_out.normal = gs_in[2].normal;
        gs_out.basecolor = vec3(gs_in[0].level,gs_in[1].level,gs_in[2].level)/6.0;
        gs_out.texCoord =  gl_in[2].gl_Position;
        EmitVertex();

        EndPrimitive();
    }

}  