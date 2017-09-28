#version 410

layout(location = 0) in vec4 position; 
layout(location=1) in vec4 color; 
out vec4 vColor; 
uniform mat4 projectionViewWorldMatrix;
uniform float time;
void main() 
{ 
	vColor = color;
	vec4 displ = vec4(cos(time), sin(time), sin(time)/cos(time), 1);
	vec4 newpos = position;// + displ;
	gl_Position = projectionViewWorldMatrix * newpos; 
}