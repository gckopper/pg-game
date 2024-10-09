// shader sketch

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 i_tex_diff;
layout (location = 2) in vec2 i_tex_coord;

uniform float time_diff;
out vec2 tex_coord;

void main() {
    // 2D only
    gl_Position = vec4(position, 1.0, 1.0);
    tex_coord = i_tex_coord + time_diff*i_tex_diff;
};
