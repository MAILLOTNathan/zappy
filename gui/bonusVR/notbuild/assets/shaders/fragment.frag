#version 320 es
precision mediump float;

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec2 TexCoords;

layout(location = 3) uniform sampler2D texture_diffuse1;
layout(location = 4) uniform sampler2D texture_specular1;
layout(location = 5) uniform sampler2D texture_normal1;
layout(location = 6) uniform sampler2D texture_height1;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}