#include "ui/ImGuiLayer.h"
#include "ui/BoidsParams.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "core/Simulation.h"
#include "Utils/WindowInfo.h"

class Application {
private:
    static Application* s_Instance;
    GLFWwindow* m_Window = nullptr;
    bool m_Running = true;
    std::unique_ptr<Boids::ImGuiLayer> m_ImGuiLayer;
    BoidsParams m_BoidsParams;
    Boids::Simulation m_Simulation;
    std::unique_ptr<WindowInfo> m_WindowInfo = std::make_unique<WindowInfo>();

    Application() = default;
    ~Application() = default;

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool init();
    void mainLoop();
    void cleanup();

public:
    static Application& get() {
        if (!s_Instance) {
            s_Instance = new Application();
        }
        return *s_Instance;
    }

    int run() {
        if (!init()) return 1;
        mainLoop();
        cleanup();
        return 0;
    }
};

Application* Application::s_Instance = nullptr;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

bool Application::init() {
    m_Simulation.initialize(m_BoidsParams);
    // Initialize GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return false;

    // Create window
    m_Window = glfwCreateWindow(1280, 720, "Boids Simulation", nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    // Initialize GLAD
    if (!gladLoadGL()) {
        printf("Failed to initialize GLAD\n");
        return false;
    }

    // Print OpenGL version
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Set clear color to dark gray
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Create and initialize ImGui layer
    m_ImGuiLayer = Boids::ImGuiLayer::Create(m_Window);
    m_ImGuiLayer->OnAttach();

    // TODO: Make sure the widget is adjusted to the window size
    m_ImGuiLayer->RegisterWindow("Boids Parameters", [this]() {
        if (ImGui::CollapsingHeader("Global Simulation Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderInt("Boid Count", &m_BoidsParams.boidCount, 10, 1000);
            ImGui::SliderFloat("Simulation Speed", &m_BoidsParams.simulationSpeed, 0.1f, 5.0f);
        }
        if (ImGui::CollapsingHeader("Movement Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderFloat("Max Speed", &m_BoidsParams.maxSpeed, 0.1f, 10.0f);
            ImGui::SliderFloat("Max Force", &m_BoidsParams.maxForce, 0.01f, 1.0f);
        }
        if (ImGui::CollapsingHeader("Behavior weights", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderFloat("Alignment Weight", &m_BoidsParams.alignmentWeight, 0.0f, 5.0f);
            ImGui::SliderFloat("Separation Weight", &m_BoidsParams.separationWeight, 0.0f, 5.0f);
            ImGui::SliderFloat("Cohesion Weight", &m_BoidsParams.cohesionWeight, 0.0f, 5.0f);
        }
    });

    return true;
}


// TODO: Add a viewport class to handle info about the viewport and the camera
void Application::mainLoop() {
    while (!glfwWindowShouldClose(m_Window) && m_Running) {
        // Clear both color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        // Update viewport
        int width = 0, height = 0;
        glfwGetWindowSize(m_Window, &width, &height);
        glViewport(0, 0, width, height);
        m_WindowInfo->resize(width, height);

        // Use ImGui layer to update and render
        m_ImGuiLayer->OnUpdate(0.0f, m_WindowInfo.get()); 
        
        // Simulation update and render
        m_Simulation.update(0.001f, m_BoidsParams);
        m_Simulation.render();

        glfwSwapBuffers(m_Window);
    }
}

void Application::cleanup() {
    m_ImGuiLayer->OnDetach();
    m_ImGuiLayer.reset();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

int main(int, char**) {
    return Application::get().run();
}