#version 410 core

layout(location = 0) out vec4 fragColor;
in vec2 v_texCoord;

uniform sampler2D u_Texture;

void main() {
    vec4 texColor = texture(u_Texture,v_texCoord);
    fragColor = texColor;
}
