#pragma once
#include <GLFW/glfw3.h>
#include "bgfx/bgfx.h"

namespace Boids {
    class BGFXTest {
    public:
        static bool shouldClose();  
        static void pollEvents();   
        static bool isKeyPressed(int key);  
        static GLFWwindow* window;
    };
}