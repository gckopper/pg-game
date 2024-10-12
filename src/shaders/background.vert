layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_delta;
layout (location = 2) in vec2 texture_position;

out vec2 tex_coord;

uniform float delta_time;

void main() {
    // 2D only
    gl_Position = vec4(position, 1.0, 1.0);
    tex_coord = texture_position + delta_time*texture_delta;
};
