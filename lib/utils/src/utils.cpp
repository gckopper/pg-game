#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/log.hpp>
#include <game/utils.hpp>

GLFWwindow* gm::init_context(int width, int height, std::string title) {
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

    if (gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) == 0) {
        LOG("Failed to initialize OpenGL context");
        terminate();
    }

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    return window;
}

void gm::terminate() {
    glfwTerminate();
    std::abort();
}

void gm::glfw_error_callback(int code, const char* desc) {
    LOG("GLFW encountered an error:" << code);
    LOG(desc);

    terminate();
}

void gm::glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    float scale = std::min(width / static_cast<float>(WORLD_WIDTH), height / static_cast<float>(WORLD_HEIGHT));

    int new_width  = WORLD_WIDTH  * scale;
    int new_height = WORLD_HEIGHT * scale;
    
    glViewport((width - new_width) / 2, (height - new_height) / 2, new_width, new_height);
}
