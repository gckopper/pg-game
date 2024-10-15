
#include <game/time.hpp>
#include <game/types.hpp>
#include <game/render.hpp>

void gm::render(uint64_t time_delta, Entities& entities, Background& background, Healthbar& healthbar, Font& font) {
    const float time = time_delta / static_cast<float>(TICK_STEP.count());

    glClear(GL_COLOR_BUFFER_BIT);
    
    // background
    glUseProgram(background.shader_program);
    glBindTexture(GL_TEXTURE_2D, background.texture);
    glBindVertexArray(background.vao);

    glUniform1f(background.u_time_delta, time);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    // entities
    glUseProgram(entities.shader_program);
    glBindTexture(GL_TEXTURE_2D, entities.texture);
    glBindVertexArray(entities.vao);

    glUniform1f(entities.u_time_delta, time);

    glDrawElements(GL_TRIANGLES, 6*(entities.enemy_count), GL_UNSIGNED_SHORT, reinterpret_cast<const void*>(6*sizeof(GLshort)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    // healthbar
    glUseProgram(healthbar.shader_program);
    glBindTexture(GL_TEXTURE_2D, healthbar.texture);
    glBindVertexArray(healthbar.vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    // text
    glUseProgram(font.shader);
    glBindTexture(GL_TEXTURE_2D, font.texture);
    glBindVertexArray(font.vao);

    glDrawElements(GL_TRIANGLES, 6 * (font.offset/16), GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
