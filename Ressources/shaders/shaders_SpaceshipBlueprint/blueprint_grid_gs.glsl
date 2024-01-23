#version 450 core
layout (points) in;
layout (line_strip, max_vertices = 16) out;


uniform mat4 u_view_projection;
uniform int u_show_level;
uniform int u_vertices_per_level;
uniform vec3 u_stepsize;

out vec3 GridColor;

in int VertexID[];
in float val[];

void EmitLine(vec3 A, vec3 B)
{
	gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(A,0.0));
    EmitVertex();
	gl_Position = u_view_projection * (gl_in[0].gl_Position + vec4(B,0.0));
    EmitVertex();
	EndPrimitive();
}

void main() 
{    
    
    // Create grid
    float dx = u_stepsize.x/2;
    float dz = u_stepsize.z/2;

    int low_bound = u_vertices_per_level * (u_show_level);
    int high_bound = u_vertices_per_level * (u_show_level+1);

    if(val[0] > 0.0)
        GridColor = vec3(1.0,0.0,0.0); //val[0]/100,0.0,0.0
    else if(val[0] == 0.0)
        GridColor = vec3(0.0,0.0,1.0);
    else
        GridColor = vec3(0.2,0.8,0.2);

    if (false || (VertexID[0] >= low_bound) && (VertexID[0] < high_bound)) 
    {

//        EmitLine(vec3(-dx,0.0,-dz),vec3(-dx,0.0,dz));
//        EmitLine(vec3(-dx,0.0,-dz),vec3(dx,0.0,-dz));
//

        //  Grid of points
        EmitLine(vec3(-dx/4,0.0,0.0),vec3(dx/4,0.0,0.0));
        EmitLine(vec3(0.0,0.0,-dz/4),vec3(0.0,0.0,+dz/4));

        EmitLine(vec3(-2*dx/5,0.0,0.0),vec3(-4*dx/5,0.0,0.0));
        EmitLine(vec3(0.0,0.0,-2*dz/5),vec3(0.0,0.0,-4*dz/5));

        EmitLine(vec3(2*dx/5,0.0,0.0),vec3(4*dx/5,0.0,0.0));
        EmitLine(vec3(0.0,0.0,2*dz/5),vec3(0.0,0.0,4*dz/5));
//        EmitLine(vec3(-dx/4,0.0,0.0),vec3(dx/4,0.0,0.0));
//        EmitLine(vec3(0.0,0.0,-dz/4),vec3(0.0,0.0,+dz/4));

    }

// PASS THROUGH
//    gl_Position =  u_view_projection * gl_in[0].gl_Position;
//    EmitVertex();
//    EndPrimitive();


}  