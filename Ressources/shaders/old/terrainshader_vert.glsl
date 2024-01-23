#version 450 core
layout (location = 0) in float altitude;
layout (location = 1) in float normal;

out vec2 TexCoord;

uniform mat4 u_model;
uniform mat4 u_view_projection;
uniform int chunkIndex;
uniform float TERRAIN_SIZE;

void main()
{
	float size = 8; /*1756.0*/
	float VERTICES_PER_RUN         = 2.0*size + 1.0 + 3.0; /* account for the 2 vertices supp per row */
	float CLAMPED_VERTICES_PER_RUN = 2.0*size + 1.0;

	float rowIndex = mod(gl_VertexID, VERTICES_PER_RUN);
	float ID = clamp(rowIndex - 1.0, 0.0, CLAMPED_VERTICES_PER_RUN);

	vec3 position = vec3(0.0);
	position.x = floor( ID  / 2.0);
	position.z = mod( ID , 2.0);

	position.z += floor(gl_VertexID / VERTICES_PER_RUN);

	position.y = altitude / 4.0;

	TexCoord = vec2(position.xz/size*size);  /* size */

	/* scale */
	float scale = 1.0;

	position *= scale;

	/* chunks */
	float num_chunks_row = 256 / size;
	position.x +=  mod(chunkIndex,num_chunks_row) * (size + 0.0);
	position.z +=  floor(chunkIndex/num_chunks_row) * (size + 0.0);

	gl_Position = u_view_projection * vec4(position, 1.0);
	
}