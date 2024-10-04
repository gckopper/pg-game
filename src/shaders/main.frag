// shader sketch

in vec2 tex_coord;

out vec4 color;

uniform sampler2D ourTexture;

void main() {
    color = texture(ourTexture, tex_coord);
};
