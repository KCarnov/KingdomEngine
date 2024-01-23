#version 450 core
layout (location = 0) in float aAltitude;
layout (location = 1) in float aAngle;

out vec2 TexCoord;

uniform mat4 u_model;
uniform mat4 u_view_projection;

void main()
{

	float VERTICES_PER_RUN = 20.0;
	float CLAMPED_VERTICES_PER_RUN = 17.0;

	float rowIndex = mod(gl_VertexID, VERTICES_PER_RUN);
	float ID = clamp(rowIndex - 1.0, 0.0, CLAMPED_VERTICES_PER_RUN);

	vec3 position = vec3(0.0);
	position.x = floor( ID  / 2.0);
	position.z = mod( ID , 2.0);

	position.z += floor(gl_VertexID / VERTICES_PER_RUN);
	position.y = aAltitude;

	TexCoord = vec2(position.xz/8.0); 

	gl_Position = u_view_projection * vec4(position, 1.0);
	
}