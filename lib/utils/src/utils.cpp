#include <game/utils.hpp>

#include <game/log.hpp>
#include <cstdlib>

GLFWwindow* gm::setup_glfw(int width, int height, std::string title) {
    if (glfwInit() == GLFW_FALSE) {
        LOG("Failed to create GLFW context");
        terminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
    if (gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) == 0) {
        LOG("Failed to initialize OpenGL context");
        terminate();
    }
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
	glViewport(fb_width, fb_height, fb_width, fb_height);
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
