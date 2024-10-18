layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 in_tex_coord;
layout (location = 2) in vec2 pos_instanced;
layout (location = 3) in vec2 in_tex_coord_instanced;
layout (location = 4) in float size;

out vec2 tex_coord;

mat4 projection = mat4(
     0.003125f, 0.0f,         0.0f, 0.0f,
     0.0f,      0.00555556f,  0.0f, 0.0f,
     0.0f,      0.0f,        -1.0f, 0.0f,
    -1.0f,     -1.0f,         0.0f, 1.0f
);

void main() {
    tex_coord = in_tex_coord + in_tex_coord_instanced;

    gl_Position = projection * vec4(vec2(size*pos.x, size*pos.y*2) + pos_instanced, 1.0f, 1.0f);
}
