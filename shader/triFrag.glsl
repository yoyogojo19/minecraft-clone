#version 460

in vec2 texCoords;
out vec4 FragColor;
uniform sampler2D Texture2D;

void main() {
    FragColor = texture(Texture2D, texCoords);
}
