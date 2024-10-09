#include <game/renderer.hpp>

#include <game/time.hpp>
#include <game/log.hpp>

void gm::render(uint64_t time_diff, GLFWwindow* window, game g) {
    constexpr float tick_duration = 1.f / static_cast<float>(TICK_RATE);
    const float percentage = static_cast<float>(time_diff) / (1000000.f * tick_duration);
    
    glUseProgram(g.bg.render.shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g.bg.render.tex);
    glBindVertexArray(g.bg.render.vao);

    glUniform1i(g.bg.render.u_tex, 0);
    glUniform1f(g.bg.render.u_time, percentage);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(g.entity_render.shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g.entity_render.tex);
    glBindVertexArray(g.entity_render.vao);
    glUniform1i(g.entity_render.u_tex, 0);
    glUniform1f(g.entity_render.u_time, percentage);
    // missing projection matrix uniform

    glDrawElements(GL_TRIANGLES, 6*(1+g.mobs_count), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glfwSwapBuffers(window);
}
