#include <game/log.hpp>
#include <game/texture.hpp>
#include <game/utils.hpp>

GLuint gm::load_texture(std::string path) {
    stbi_set_flip_vertically_on_load(1);
    
    int height, width, n;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &n, 0);
    if (data == 0) {
        LOG("Failed to load texture " << path);
        terminate();
    }
    GLuint texture;
    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return texture;
}
