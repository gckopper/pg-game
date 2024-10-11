#include <array>
#include <cmath>
#include <cstdint>

#include <glad/glad.h>

#include <game/entity.hpp>
#include <game/shader.hpp>
#include <game/sprite.hpp>
#include <game/texture.hpp>
#include <game/utils.hpp>

void gm::setup_entities(entities& entities) {
    entities.shader_program = gm::make_shader_program("entities.vert", "entities.frag");
    entities.texture = gm::load_texture("./assets/atlas.png");
    entities.enemy_count = 0;

    // player vbo data
    player& p = entities.player;

    // vertex positions (tr -> br -> bl -> tl)
    entities.vbo_data[0]  = std::ceil((WORLD_WIDTH  + SPRITE_SIZE) / 2.0f);
    entities.vbo_data[1]  = std::ceil((WORLD_HEIGHT + SPRITE_SIZE) / 2.0f);
    entities.vbo_data[6]  = std::ceil((WORLD_WIDTH  + SPRITE_SIZE) / 2.0f);
    entities.vbo_data[7]  = std::ceil((WORLD_HEIGHT - SPRITE_SIZE) / 2.0f);
    entities.vbo_data[12] = std::ceil((WORLD_WIDTH  - SPRITE_SIZE) / 2.0f);
    entities.vbo_data[13] = std::ceil((WORLD_HEIGHT - SPRITE_SIZE) / 2.0f);
    entities.vbo_data[18] = std::ceil((WORLD_WIDTH  - SPRITE_SIZE) / 2.0f);
    entities.vbo_data[19] = std::ceil((WORLD_HEIGHT + SPRITE_SIZE) / 2.0f);

    // texture positions (tr -> br -> bl -> tl)
    entities.vbo_data[2]  = SPRITE_SIZE / static_cast<GLfloat>(ATLAS_WIDTH);
    entities.vbo_data[3]  = (p.sprite->ATLAS_POS + SPRITE_SIZE) / static_cast<GLfloat>(ATLAS_HEIGHT);
    entities.vbo_data[8]  = SPRITE_SIZE / static_cast<GLfloat>(ATLAS_WIDTH);
    entities.vbo_data[9]  = p.sprite->ATLAS_POS / static_cast<GLfloat>(ATLAS_HEIGHT);
    entities.vbo_data[14] = 0.0f;
    entities.vbo_data[15] = p.sprite->ATLAS_POS / static_cast<GLfloat>(ATLAS_HEIGHT);
    entities.vbo_data[20] = 0.0f;
    entities.vbo_data[21] = (p.sprite->ATLAS_POS + SPRITE_SIZE) / static_cast<GLfloat>(ATLAS_HEIGHT);

    // delta pos
    for (uint8_t i = 0; i < 4; ++i) {
        entities.vbo_data[i * 6 + 4] = 0.0f;
        entities.vbo_data[i * 6 + 5] = 0.0f;
    }
    
    glGenVertexArrays(1, &entities.vao);
    glBindVertexArray(entities.vao);

    glGenBuffers(1, &entities.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, entities.vbo);
    glBufferData(GL_ARRAY_BUFFER, entities.vbo_data.size() * sizeof(GLfloat), entities.vbo_data.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (2 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (4 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // ebo data
    constexpr std::array<GLushort, 6> square{0, 1, 3, 1, 2, 3};
    for (uint16_t i = 0; i <= MAX_ENEMIES; ++i) {
        for (uint8_t j = 0; j < 6; ++j) {
            entities.ebo_data[i * 6 + j] = square[j] + i * 4;
        }
    }

    glGenBuffers(1, &entities.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entities.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, entities.ebo_data.size() * sizeof(GLushort), entities.ebo_data.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}