// src/ui/ImGuiLayer.cpp
#include "ImGuiLayer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

namespace Boids {

class ImGuiLayer::Impl {
public:
    Impl(GLFWwindow* window) : window(window) {
        // Initialize ImGui
        IMGUI_CHECKVERSION();
        context = ImGui::CreateContext();
        ImGui::SetCurrentContext(context);
        
        // Configure ImGui
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard navigation

        // Set style
        ImGui::StyleColorsDark();
        
        // Set platform/renderer backend
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    ~Impl() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(context);
    }

    void BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void RenderWindows(const WindowInfo* windowInfo) {
        int winWidth = windowInfo->getWidth();
        int winHeight = windowInfo->getHeight();

        // TODO： will parameterize these data later
        float posXRatio = 0.05f, posYRatio = 0.05f;
        float widthRatio = 0.2f, heightRatio = 0.35f;

        for (const auto& [name, callback] : windows) {
            ImVec2 pos(winWidth * posXRatio, winHeight * posYRatio);
            ImVec2 size(winWidth * widthRatio, winHeight * heightRatio);

            ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(size, ImGuiCond_Always);

            ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            callback();
            ImGui::End();
        }
    }

    // Window management
    std::unordered_map<std::string, WindowCallback> windows;
    
    // Theme management
    void SaveTheme(const std::string& name) {
        // TODO: Implement theme saving
    }

    void LoadTheme(const std::string& name) {
        // TODO: Implement theme loading
    }

    // Layout management
    void SaveLayout(const std::string& name) {
        // TODO: Implement layout saving
    }

    void LoadLayout(const std::string& name) {
        // TODO: Implement layout loading
    }

private:
    GLFWwindow* window;
    ImGuiContext* context;
};

// Factory method implementation
std::unique_ptr<ImGuiLayer> ImGuiLayer::Create(GLFWwindow* window) {
    auto layer = std::unique_ptr<ImGuiLayer>(new ImGuiLayer());
    layer->pImpl = std::make_unique<Impl>(window);
    return layer;
}

ImGuiLayer::ImGuiLayer() = default;
ImGuiLayer::~ImGuiLayer() = default;

void ImGuiLayer::OnAttach() {
    // Additional initialization can be done here
}

void ImGuiLayer::OnDetach() {
    // Additional cleanup can be done here
}

void ImGuiLayer::OnUpdate(float deltaTime, const WindowInfo* windowInfo) {
    pImpl->BeginFrame();
    pImpl->RenderWindows(windowInfo);
    pImpl->EndFrame();
}

void ImGuiLayer::OnRender() {
    // Rendering is handled in OnUpdate
}

void ImGuiLayer::RegisterWindow(const std::string& name, WindowCallback callback) {
    pImpl->windows[name] = std::move(callback);
}

void ImGuiLayer::UnregisterWindow(const std::string& name) {
    pImpl->windows.erase(name);
}

void ImGuiLayer::SetTheme(const std::string& themeName) {
    pImpl->LoadTheme(themeName);
}

void ImGuiLayer::SaveTheme(const std::string& themeName) {
    pImpl->SaveTheme(themeName);
}

void ImGuiLayer::LoadTheme(const std::string& themeName) {
    pImpl->LoadTheme(themeName);
}

void ImGuiLayer::SaveLayout(const std::string& layoutName) {
    pImpl->SaveLayout(layoutName);
}

void ImGuiLayer::LoadLayout(const std::string& layoutName) {
    pImpl->LoadLayout(layoutName);
}

void ImGuiLayer::ResetLayout() {
    // TODO: Implement layout reset
}

} // namespace Boids