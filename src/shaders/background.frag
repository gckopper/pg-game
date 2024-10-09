// shader sketch

in vec2 tex_coord;

out vec4 color;

uniform sampler2D our_texture;

void main() {
    color = texture(our_texture, tex_coord);
};
