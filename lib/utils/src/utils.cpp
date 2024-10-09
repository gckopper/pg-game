#include <game/types.hpp> 
#include <game/utils.hpp>
#include <game/log.hpp>

#include <array>

GLFWwindow* gm::setup_glfw(int width, int height, std::string title) {
    if (glfwInit() == GLFW_FALSE) {
        LOG("Failed to create GLFW context");
        terminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
    if (gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) == 0) {
        LOG("Failed to initialize OpenGL context");
        terminate();
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
	glViewport(0, 0, fb_width, fb_height);
    return window;
}

void gm::setup_buffers(game &g) {
    constexpr std::array<float, 24> bg_vbo = {
            -1.0f, -1.0f, 0.f, 0.f,  0.f,   0.f,   // bottom left
            -1.0f,  1.0f, 0.f, 0.f,  0.f,   0.9f,  // top left
             1.0f,  1.0f, 0.f, 0.f,  1.6f,  0.9f,  // top right
             1.0f, -1.0f, 0.f, 0.f,  1.6f,  0.f,}; // bottom right
    constexpr std::array<float, 24> player_vbo = {
            WIDTH/2.f-18.f, HEIGHT/2.f-18.f, 0.f, 0.f, -0.75f, 0.6f,
            WIDTH/2.f-18.f, HEIGHT/2.f+18.f, 0.f, 0.f, -0.75f, 1.f,
            WIDTH/2.f+18.f, HEIGHT/2.f+18.f, 0.f, 0.f, -1.0f,  1.f,
            WIDTH/2.f+18.f, HEIGHT/2.f-18.f, 0.f, 0.f, -1.0f,  0.6f,};
    const std::array<uint32_t, 6> square = {0,1,2, 0,2,3};
    std::array<uint32_t, square.size()*(MAX_MOBS+1)> squares = {0};
    for (uint32_t i = 0; i < (MAX_MOBS+1); ++i) {
        for (uint32_t j = 0; j < square.size(); ++j) {
            squares[i*square.size()+j] = square[j]+i*square.size();
        }
    }


    glGenBuffers(1, &g.bg.render.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g.bg.render.vbo);
    glBufferData(GL_ARRAY_BUFFER, bg_vbo.size()*sizeof(float), bg_vbo.data(), GL_DYNAMIC_DRAW);

    glGenVertexArrays(1, &g.bg.render.vao);
    glBindVertexArray(g.bg.render.vao);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERT_SIZE, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERT_SIZE, (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERT_SIZE, (void*)(4*sizeof(float)));
    glEnableVertexAttribArray(2);

    GLuint bg_ebo;
    glGenBuffers(1, &bg_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bg_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, square.size()*sizeof(uint32_t), square.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenBuffers(1, &g.entity_render.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g.entity_render.vbo);
    glBufferData(GL_ARRAY_BUFFER, gm::VERT_SIZE*(1+MAX_MOBS), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, player_vbo.size()*sizeof(float), player_vbo.data());

    glGenVertexArrays(1, &g.entity_render.vao);
    glBindVertexArray(g.entity_render.vao);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERT_SIZE, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERT_SIZE, (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERT_SIZE, (void*)(4*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    GLuint entity_ebo;
    glGenBuffers(1, &entity_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, squares.size()*sizeof(uint32_t), squares.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
