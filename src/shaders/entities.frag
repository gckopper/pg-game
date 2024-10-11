in vec2 tex_coord;
in vec2 delta_pos;

out vec4 color;

uniform sampler2D texture_uniform;

void main() {
    color = texture(texture_uniform, tex_coord + delta_pos);
}