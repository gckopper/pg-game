
#include <game/time.hpp>
#include <game/types.hpp>
#include <game/render.hpp>

void gm::render(uint64_t time_delta, Entities& entities, Background& background) {
    const float time = time_delta / static_cast<float>(TICK_STEP.count());

    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(background.shader_program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, background.texture);
    glBindVertexArray(background.vao);

    glUniform1f(background.u_time_delta, time);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glUseProgram(entities.shader_program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entities.texture);
    glBindVertexArray(entities.vao);
    glUniform1f(entities.u_time_delta, time);

    glDrawElements(GL_TRIANGLES, 6*(1+entities.enemy_count), GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

