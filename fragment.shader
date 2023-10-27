#version 410 core
in vec2 out_texCoord;
out vec4 fragColor;

uniform sampler2D gSampler;

void main()
{
    fragColor = texture(gSampler, out_texCoord);
    // fragColor = vec4(255, 1.0, 1.0, 1.0);
}