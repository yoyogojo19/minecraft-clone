#version 460

layout(point) in;
layout(triangle_strip, max_verticies = 4) out;

in ivec3 extra;
in vec2 tcoords[];
out vec2 texCoords;

void main() {
    gl_Position = gl_in[0].gl_Position;
    texCoords = tcoords[0];
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(float(extra.x), 0.0, 0.0, 0.0);
    texCoords = tcoords[0] + vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.0, float(extra.y), 0.0, 0.0);
    texCoords = tcoords[0] + vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(float(extra.x), float(extra.y), 0.0, 0.0);
    texCoords = tcoords[0] + vec2(1.0);
    EmitVertex();

    EndPrimitive();
}
