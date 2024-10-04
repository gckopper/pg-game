#include <game/texture.hpp>

#include <game/log.hpp>

GLuint gm::load_texture(std::string path) {
    int height, width, n;
    unsigned char* data = stbi_load(path.c_str(), &height, &width, &n, 0);
    if (data == 0) {
        LOG("Failed to load texture " << path);
        terminate();
    }
    GLuint texture;
    glGenTextures(1, &texture);
    
    // explore the usage of glActiveTexture here

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return texture;
}
