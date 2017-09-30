#version 410

in vec4 vNormal;
in vec4 vPosition;
in vec4 vColor;
in vec2 vUV;


out vec4 outColor;

uniform sampler2D tex;

void main()
{
	outColor = texture(tex, vUV);
}