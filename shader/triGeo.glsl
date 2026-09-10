#version 460 core

layout(point) in;
layout(triangle_strip, max_verticies = 4) out;

in ivec3 extra[];
out vec2 gUV;

void main() {
    gl_Position = gl_in[0].gl_Position;
    gUV = vec2(0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(float(extra[0].x), 0.0, 0.0, 0.0);
    gUV = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.0, float(extra[0].y), 0.0, 0.0);
    gUV = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(float(extra[0].x), float(extra[0].y), 0.0, 0.0);
    gUV = vec2(1.0);
    EmitVertex();

    EndPrimitive();
}
