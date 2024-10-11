in vec2 tex_coord;

out vec4 color;

uniform sampler2D texture_uniform;

void main() {
    color = texture(texture_uniform, tex_coord);
}