#version 410
\n \
layout(location = 0) in vec4 position; \
layout(location=1) in vec4 color; \
out vec4 vColor; \
uniform mat4 projectionViewWorldMatrix; \
oid main() { 
vColor = color; gl_Position = projectionViewWorldMatrix * position; 
}