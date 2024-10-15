layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 in_tex_coord;

out vec2 tex_coord;

mat4 projection = mat4(
     0.003125f, 0.0f,         0.0f, 0.0f,
     0.0f,      0.00555556f,  0.0f, 0.0f,
     0.0f,      0.0f,        -1.0f, 0.0f,
    -1.0f,     -1.0f,         0.0f, 1.0f
);

void main() {
    tex_coord = in_tex_coord;

    gl_Position = projection * vec4(pos, 1.0f, 1.0f);
}
