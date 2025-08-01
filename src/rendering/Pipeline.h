// src/rendering/Pipeline.h
#pragma once

// Disable Windows min and max macros to avoid conflicts with GLM
#define NOMINMAX

#include <vector>
#include <memory>
#include <unordered_map>
#include "PipelineStage.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>  // For getting native window handle
#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Boids {
namespace Rendering {

class Pipeline {
   public:
    struct Options {
        bool triangles = false;
        bool texture = false;
        bool vertices = false;
        bool showGrid = true;

        void Reset() {
            triangles = false;
            texture = false;
            vertices = false;
            showGrid = true;
        }
    };

    Pipeline();
    ~Pipeline();

    void Initialize(GLFWwindow* window, int width, int height);
    void Shutdown();

    void AddStage(std::unique_ptr<PipelineStage> stage);
    void RemoveStage(const std::string& name);
    void EnableStage(const std::string& name, bool enabled);

    void Execute();

    Options& GetOptions() { return m_Options; }
    const Options& GetOptions() const { return m_Options; }

    PipelineStage* GetStage(const std::string& name);

   private:

    bool m_BGFXInitialized = false;

    std::vector<StagePtr> m_Stages;
    std::unordered_map<std::string, PipelineStage*> m_StageMap;
    Options m_Options;
};

}  // namespace Rendering
}  // namespace Boids