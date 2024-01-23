#version 450 core
layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;

in float Cave[];
in float Height[];
in TEShaderOut {
	vec2 texCoord;
	vec2 texCoord2;
} tes_in[];

out gShaderOut {
	vec2 texCoord;
	vec2 texCoord2;
} fs_in;

out float gCave;
out float gHeight;

void main() 
{    

	int i;
    for (i = 0; i < gl_in.length(); i++)
    {
        if(Cave[i] < 1.0){
        gl_Position = gl_in[i].gl_Position;
        fs_in.texCoord = tes_in[i].texCoord; 
	    fs_in.texCoord2 = tes_in[i].texCoord2; 
        gCave = Cave[i];
        gHeight = Height[i];
        EmitVertex();
        }
    }
    EndPrimitive();

}  