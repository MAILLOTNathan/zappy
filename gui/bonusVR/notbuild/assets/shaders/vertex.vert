#version 320 es
precision mediump float;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

layout(location = 0) out vec2 TexCoords;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view_proj;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = view_proj * model * vec4(aPos, 1.0);
}