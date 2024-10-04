#pragma once

#include <glad/glad.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace gm {
    GLuint load_texture(std::string path);
}
