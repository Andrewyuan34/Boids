#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../viewport/Viewport.h"

// Forward declarations
struct GLFWwindow;
struct ImGuiContext;

namespace Boids {

// Use PIMPL pattern to hide implementation details
class ImGuiLayer {
   public:
    // Use smart pointer to manage resources
    static std::unique_ptr<ImGuiLayer> Create(GLFWwindow* window);
    ~ImGuiLayer();

    ImGuiLayer(const ImGuiLayer&) = delete;
    ImGuiLayer& operator=(const ImGuiLayer&) = delete;

    ImGuiLayer(ImGuiLayer&&) noexcept = default;
    ImGuiLayer& operator=(ImGuiLayer&&) noexcept = default;

    // Lifecycle management
    void OnAttach();
    void OnDetach();
    void OnUpdate(float deltaTime, const Viewport* viewport);
    void OnRender();

    // Window management
    void BeginFrame();
    void EndFrame();

    // Window registration system
    using WindowCallback = std::function<void()>;
    void RegisterWindow(const std::string& name, WindowCallback callback);
    void UnregisterWindow(const std::string& name);

    // Theme management
    void SetTheme(const std::string& themeName);
    void SaveTheme(const std::string& themeName);
    void LoadTheme(const std::string& themeName);

    // Layout management
    void SaveLayout(const std::string& layoutName);
    void LoadLayout(const std::string& layoutName);
    void ResetLayout();

   private:
    // Use PIMPL pattern to hide implementation details
    class Impl;
    std::unique_ptr<Impl> pImpl;

    // Private constructor, force using Create factory method
    ImGuiLayer();
};

}  // namespace Boids