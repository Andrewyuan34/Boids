#include <cstdio>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ui/BoidsParams.h"
#include "ui/ImGuiLayer.h"
#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "utils/WindowInfo.h"
#include "core/Simulation.h"
#include "utils/Log.h"
#include "utils/Camera.h"

class Application {
   private:
    static Application* s_Instance;
    GLFWwindow* m_Window = nullptr;
    bool m_Running = true;
    std::unique_ptr<Boids::ImGuiLayer> m_ImGuiLayer;
    Boids::Simulation m_Simulation;
    std::unique_ptr<WindowInfo> m_WindowInfo = std::make_unique<WindowInfo>();
    std::unique_ptr<Boids::Utils::Camera> m_Camera;

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

    auto run() -> int {
        if (!init()) {
            return 1;
        }
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
    m_Simulation.initialize();

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

    int width = 0, height = 0;
    glfwGetWindowSize(m_Window, &width, &height);
    float aspect = (height == 0) ? 1.0f : static_cast<float>(width) / height;
    m_Camera = std::make_unique<Boids::Utils::Camera>(45.0f, aspect, 0.1f, 100.0f);

    // TODO: Make sure the widget is adjusted to the window size
    m_ImGuiLayer->RegisterWindow("Boids Parameters", [this]() {
        auto& params = BoidsParams::get();

        if (ImGui::CollapsingHeader("Global Simulation Parameters",
                                    ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderInt("Boid Count", &params.boidCount, 10, 1000);
            ImGui::SliderFloat("Simulation Speed", &params.simulationSpeed, 0.1f, 5.0f);
        }
        if (ImGui::CollapsingHeader("Movement Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderFloat("Max Speed", &params.maxSpeed, 0.1f, 10.0f);
            ImGui::SliderFloat("Max Force", &params.maxForce, 0.01f, 1.0f);
        }
        if (ImGui::CollapsingHeader("Behavior weights", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderFloat("Alignment Weight", &params.alignmentWeight, 0.0f, 5.0f);
            ImGui::SliderFloat("Separation Weight", &params.separationWeight, 0.0f, 5.0f);
            ImGui::SliderFloat("Cohesion Weight", &params.cohesionWeight, 0.0f, 5.0f);
        }

        auto& pipeline = m_Simulation.getRenderPipeline();
        auto& options = pipeline.GetOptions();

        if (ImGui::CollapsingHeader("Render Modes", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Checkbox("Show Triangles", &options.triangles);
            ImGui::Checkbox("Show Texture", &options.texture);
            ImGui::Checkbox("Show Vertices", &options.vertices);

            if (ImGui::Button("Reset to Default")) {
                options.Reset();
            }
        }
    });

    return true;
}

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

        if (m_Camera) {
            m_Camera->setAspectRatio(static_cast<float>(width) / height);
        }

        // Use ImGui layer to update and render
        m_ImGuiLayer->OnUpdate(0.0f, m_WindowInfo.get());

        // Update simulation
        m_Simulation.update(0.001f);

        // Render simulation
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
    Log::Init();
    LOG_INFO("Logger initialized");
    return Application::get().run();
}
