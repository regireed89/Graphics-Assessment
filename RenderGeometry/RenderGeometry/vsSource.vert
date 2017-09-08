#version 410

layout(location = 0) in vec4 position; 
layout(location=1) in vec4 color; 
out vec4 vColor; 
uniform mat4 projectionViewWorldMatrix;
void main() 
{ 
	vColor = color; 
	gl_Position = projectionViewWorldMatrix * position; 
}