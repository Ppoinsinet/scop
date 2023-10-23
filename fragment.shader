#version 410 core
in vec2 color;
out vec4 fragColor;

void main()
{
    fragColor = vec4(color, 1.0, 1.0);
}