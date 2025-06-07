#include "bgfx_test.h"
#include <iostream>

namespace Boids {
    GLFWwindow* BGFXTest::window = nullptr;

    bool BGFXTest::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void BGFXTest::pollEvents() {
        glfwPollEvents();
    }

    bool BGFXTest::isKeyPressed(int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }
}

int main() {
    while (!Boids::BGFXTest::shouldClose()) {
        Boids::BGFXTest::pollEvents();

        bgfx::frame();

        if (Boids::BGFXTest::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(Boids::BGFXTest::window, true);
        }
    }
    
    return 0;
}