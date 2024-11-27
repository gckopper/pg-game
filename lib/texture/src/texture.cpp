#include <game/log.hpp>
#include <game/texture.hpp>
#include <game/utils.hpp>

GLuint gm::load_texture(std::string path) {
    return load_texture(path, nullptr, nullptr);
}

GLuint gm::load_texture(std::string path, int* result_width, int* result_height) {
    stbi_set_flip_vertically_on_load(1);
    
    int height, width, n;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &n, 0);
    if (data == 0) {
        LOG("Failed to load texture " << path);
        terminate();
    }

    glActiveTexture(GL_TEXTURE0);

    GLuint texture;
    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    if (result_width != nullptr) {
        *result_width = width;
    }

    if (result_height != nullptr) {
        *result_height = height;
    }

    return texture;
}
