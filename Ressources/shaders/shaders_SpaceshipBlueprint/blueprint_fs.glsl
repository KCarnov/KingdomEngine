#version 450 core

//in vec3 fColor;
out vec4 FragColor;
in GS_OUT {
    vec3 normal;
    vec3 basecolor;
    vec4 texCoord;
} fs_in;  

uniform sampler2D u_Texture_spaceship;

const vec3 lightDir = normalize(vec3(-1.0,-0.5,0.0));

void main()
{

    // trip lanar texturing
    // in wNorm is the world-space normal of the fragment 
    vec3 wNorm = fs_in.normal;
    vec3 blending = abs( wNorm );
    blending = normalize(max(blending, 0.00001)); // Force weights to sum to 1.0 
    float b = (blending.x + blending.y + blending.z);
    blending /= vec3(b, b, b);

    vec4 xaxis = texture2D( u_Texture_spaceship, fs_in.texCoord.yz);
    vec4 yaxis = texture2D( u_Texture_spaceship, fs_in.texCoord.xz);
    vec4 zaxis = texture2D( u_Texture_spaceship, fs_in.texCoord.xy);
    // blend the results of the 3 planar projections. 
    vec4 TexColor = xaxis * blending.x + 
                    yaxis * blending.y +
                    zaxis * blending.z;

    float Ambient = 0.5;
    float Diffuse = max(0.0, dot(fs_in.normal, -lightDir));
//    vec4 TexColor = texture(u_Texture_spaceship, fs_in.texCoord);
    vec3 BaseColor =  TexColor.rgb + 0.0*vec3(0.8, 0.3, 0.4);
    FragColor = vec4((Ambient + Diffuse) * BaseColor,1.0f);
}