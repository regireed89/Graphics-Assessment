#version 410

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec4 Normal;
layout (location = 3) in vec2 UV;


uniform mat4 projectionViewWorldMatrix;
uniform float time;

out vec4 vPosition;
out vec4 vColor;
out vec4 vNormal;
out vec2 vUV;

uniform sampler2D perlinTexture;

void main()
{
	vPosition = Position;
	vColor = Color;
	vNormal = Normal;
	vUV = UV;


	vec4 newpos = vPosition;
	newpos.y += texture(perlinTexture, UV).r * 20;
	gl_Position = projectionViewWorldMatrix * newpos; 	
}