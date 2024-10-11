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
