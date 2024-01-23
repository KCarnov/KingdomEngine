#version 450 core

//how the fixed tessellator will work, and how to interpret its output
layout (quads, equal_spacing, ccw) in;

uniform mat4 u_view_projection;
uniform sampler2D u_heightmap;
uniform sampler2D texture2;
uniform sampler2D u_heightmap_caves;
uniform float u_HeightFactor;

in TCShaderOut {
	vec2 texCoord;
    vec2 texCoord2;
} tes_in[];

out TEShaderOut {
	vec2 texCoord;
    vec2 texCoord2;
} tes_out;

// send to Fragment Shader for coloring
out float Cave;
out float Height;


void main() {

    
    // get patch coordinate
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    vec2 uv = vec2(u,v);

    // ---------------------------------------------------------------------
    vec2 t21 = mix(tes_in[0].texCoord2, tes_in[1].texCoord2, gl_TessCoord.x);
	vec2 t22 = mix(tes_in[3].texCoord2, tes_in[2].texCoord2, gl_TessCoord.x);
	tes_out.texCoord2 = mix(t21, t22, gl_TessCoord.y);
    // ----------------------------------------------------------------------

    // ----------------------------------------------------------------------
    // retrieve control point texture coordinates
    vec2 uv0 = tes_in[0].texCoord;
    vec2 uv1 = tes_in[1].texCoord;
    vec2 uv2 = tes_in[2].texCoord;
    vec2 uv3 = tes_in[3].texCoord;

    // bilinearly interpolate texture coordinate across patch
    vec2 leftUV = uv0 + v * (uv3 - uv0);
    vec2 rightUV = uv1 + v * (uv2 - uv1);
    vec2 texCoord = leftUV +  u * (rightUV - leftUV);
    tes_out.texCoord = texCoord;
    vec2 baseHeight  = texture(u_heightmap, texCoord).rg;
    float baseCave   = texture(u_heightmap_caves, texCoord).g;

    Height = baseHeight.r * u_HeightFactor;
    Cave = baseHeight.g;

    // ----------------------------------------------------------------------
    // retrieve control point position coordinates
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 p3 = gl_in[3].gl_Position;

    // compute patch surface normal
    vec4 uVec = p1 - p0;
    vec4 vVec = p3 - p0;
//    vec4 normal = normalize( vec4(cross(vVec.xyz, uVec.xyz), 0) );
    vec4 normal = vec4(0.0,1.0,0.0,0.0);
    

    // bilinearly interpolate position coordinate across patch
    vec4 leftPos  = p0 + v * (p3 - p0);
    vec4 rightPos = p1 + v * (p2 - p1);
    vec4 tes_point = leftPos + u * (p1 - p0);

    // displace point along normal
    tes_point += normal * Height;

    // output patch point position in clip space
    gl_Position = u_view_projection * tes_point;

}


// PATCH : 
// 3 __ 2
//      |
//	    |
//	    |
// 0 __ 1