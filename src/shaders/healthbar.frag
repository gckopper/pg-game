in vec2 tex_coord;

out vec4 color;

uniform float health_percentage;
uniform sampler2D texture_uniform;

void main() {
    float offset = tex_coord.x > health_percentage ? 0.5f : 0.0f;
    color = texture(texture_uniform, vec2(tex_coord.x, tex_coord.y / 2.0f + offset));
}
