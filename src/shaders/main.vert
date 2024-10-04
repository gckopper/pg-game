// shader sketch

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 position_diff;
layout (location = 2) in vec2 i_tex_coord;
uniform mat4 projection;
uniform float time_diff;
out vec2 o_tex_coord;

void main() {
    // 2D only
    gl_Position = projection * vec4(position+time_diff*position_diff, 1.0, 1.0);
    o_tex_coord = i_tex_coord;
};
