#version 460 core

in vec2 gUV;
out vec4 FragColor;
uniform sampler2D Texture2D;

void main() {
    FragColor = texture(Texture2D, gUV);
}
