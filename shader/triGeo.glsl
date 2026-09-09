#version 460

layout(point) in;
layout(triangle_strip, max_verticies = 4) out;

in ivec3 extra;
in vec3 vPos[];
out vec2 TextCords;

void main() {
    gl_Position = vec4(vPos[0] + float(extra.x));
}
