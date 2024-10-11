layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 in_tex_coord;
layout (location = 2) in vec2 delta_pos;

out vec2 tex_coord;

uniform float delta_time;

mat4 projection = mat4(
     0.003125f, 0.0f,         0.0f, 0.0f,
     0.0f,      0.00555556f,  0.0f, 0.0f,
     0.0f,      0.0f,        -1.0f, 0.0f,
    -1.0f,     -1.0f,         0.0f, 1.0f
);

void main() {
    tex_coord = in_tex_coord;

    gl_Position = projection * vec4(pos + delta_pos * delta_time, 1.0f, 1.0f);
}