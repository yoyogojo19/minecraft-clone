#version 460 core
layout(location=0) in uint aPos;

out ivec3 extra;

vec3 getPos(uint num) {
    float x = float(num       & 31U);
    float y = float(num << 5  & 31U);
    float z = float(num << 10 & 31U);
    int w =   int(  num << 15 & 31U);
    int h =   int(  num << 20 & 31U);
    int dir = int(  num << 25 & 7U );
    extra = ivec3(w, h, dir);
    return vec3(x, y, z);
}

uniform float time;
uniform mat4 proj;
uniform mat4 view;

void main() {
    gl_Position = proj * view * vec4(getPos(aPos) * 0.5, 1.0);
}
