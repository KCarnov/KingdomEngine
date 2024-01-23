#version 450 core

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
in float gHeight;
in float gCave;
//in TEShaderOut {
//	vec2 texCoord;
//	vec2 texCoord2;
//} fs_in;

in gShaderOut {
	vec2 texCoord;
	vec2 texCoord2;
} fs_in;

out vec4 FragColor;

const vec3 lightDir = normalize(vec3(-1.0,-1.0,0.0));

void main() 
{
	float Height = gHeight;
	float h = (Height + 16)/64.0f;
	float HEIGHT_SCALE = 128.0f;
	float uTexelSize = 1.0/256.0;
	float left  = texture(texture1, fs_in.texCoord + vec2(-uTexelSize, 0.0)).r * HEIGHT_SCALE * 2.0 - 1.0;
	float right = texture(texture1, fs_in.texCoord + vec2( uTexelSize, 0.0)).r * HEIGHT_SCALE * 2.0 - 1.0;
	float up    = texture(texture1, fs_in.texCoord + vec2(0.0,  uTexelSize)).r * HEIGHT_SCALE * 2.0 - 1.0;
	float down  = texture(texture1, fs_in.texCoord + vec2(0.0, -uTexelSize)).r * HEIGHT_SCALE * 2.0 - 1.0;
	vec3 normal = normalize(vec3(down - up, 2.0, left - right));

	float diff = max(0.0, dot(normal, -lightDir));
	float ambient = 0.5;

	vec4 Color = (ambient + diff) * texture(texture2, fs_in.texCoord2);

	
	
	FragColor = vec4(Color.xyz, 1.0);
//	FragColor = vec4(vec3(Height), 1.0);
}