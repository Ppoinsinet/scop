#version 410 core

layout(location = 0) in vec3 position;
// layout(location = 1) in vec2 texCoord;
// out vec2 out_texCoord;

uniform mat4 gWorld;

void main(void)
{

    gl_Position = gWorld * vec4(position, 1.0);
    // out_texCoord = texCoord;
}