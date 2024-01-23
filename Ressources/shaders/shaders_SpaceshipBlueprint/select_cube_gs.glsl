#version 450 core
layout (points) in;
layout (line_strip, max_vertices = 64) out;

uniform mat4 u_view_projection;
uniform vec3 u_stepsize;
uniform vec3 u_pos0;
uniform bool u_rectangle_selector;

void EmitLine(vec3 A, vec3 B)
{
	gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(A,0.0));
    EmitVertex();
	gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(B,0.0));
    EmitVertex();
	EndPrimitive();
}
void EmitLine2(vec3 A, vec3 B)
{
	gl_Position = u_view_projection * (vec4(A,1.0));
    EmitVertex();
	gl_Position = u_view_projection * (vec4(B,1.0));
    EmitVertex();
	EndPrimitive();
}
void main() 
{    
    float dx = u_stepsize.x/2;
    float dz = u_stepsize.z/2;
    float dy = 0.0;
//
	EmitLine(vec3(-dx,dy,-dz),vec3(-dx,dy,dz));
    EmitLine(vec3(-dx,dy,-dz),vec3(dx,dy,-dz));

	EmitLine(vec3(dx,dy,-dz),vec3(dx,dy,dz));
    EmitLine(vec3(-dx,dy,dz),vec3(dx,dy,dz));

//     little cross
	EmitLine(vec3(-dx/4,dy,0.0),vec3(dx/4,dy,0.0));
    EmitLine(vec3(0,dy,-dz/4),vec3(0,dy,dz/4));



//    if (true || u_rectangle_selector){
//
//        vec3 pos = gl_in[0].gl_Position.xyz;
//        vec3 maxz = vec3(min(pos.x,u_pos0.x),pos.y,max(pos.z,u_pos0.z));
//        vec3 maxx = vec3(max(pos.x,u_pos0.x),pos.y,min(pos.z,u_pos0.z));
//        EmitLine2(pos,u_pos0);
//        EmitLine2(pos,maxz);
//        EmitLine2(pos,maxx);
//        EmitLine2(u_pos0,maxz);
//        EmitLine2(u_pos0,maxx);
//    }
//
//	gl_Position = u_view_projection * (gl_in[0].gl_Position);
//    EmitVertex();

//    gl_Position = u_view_projection * (gl_in[1].gl_Position);
//    EmitVertex();

//    EndPrimitive();


}  