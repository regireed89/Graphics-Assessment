#version 410

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec4 Normal;
layout (location = 3) in vec4 Tangent;
layout (location = 4) in vec2 UV;

uniform mat4 projectionViewWorldMatrix;
uniform float time;
out vec4 vPosition;
out vec4 vColor;
out vec4 vNormal;
out vec4 vTangent;
out vec2 vUV;



void main()
{
	vPosition = Position;
	vColor = Color;
	vNormal = Normal;
	vUV = UV;
	vTangent = Tangent;

	vec4 newpos = vPosition;
	gl_Position = projectionViewWorldMatrix * newpos; 	
}