#include "Pipeline.h"
#include <algorithm>
#include <iostream>

// TODO: use logger instead of cout

namespace Boids {
namespace Rendering {

Pipeline::Pipeline() = default;

Pipeline::~Pipeline() = default;

void Pipeline::Initialize(GLFWwindow* window, int width, int height) {
    if (m_BGFXInitialized) {
        std::cout << "Pipeline: BGFX already initialized" << std::endl;
        return;
    }

    std::cout << "Pipeline: Initializing BGFX..." << std::endl;
    std::cout << "Pipeline: Window size: " << width << "x" << height << std::endl;

    bgfx::Init init;

    // Initialize BGFX
    if (!bgfx::init(init)) {
        std::cerr << "Pipeline: Failed to initialize BGFX" << std::endl;
        return;
    }
    
    // Set platform data
    #ifdef _WIN32
    init.platformData.nwh = glfwGetWin32Window(window);
    std::cout << "Pipeline: Windows native window handle: " << init.platformData.nwh << std::endl;
    #elif defined(__APPLE__)
    init.platformData.nwh = glfwGetCocoaWindow(window);
    #else
    init.platformData.nwh = glfwGetX11Window(window);
    #endif
    
    // Set resolution
    init.resolution.width = width;
    init.resolution.height = height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    
    std::cout << "Pipeline: BGFX init resolution: " << init.resolution.width << "x" << init.resolution.height << std::endl;

    // Check BGFX status
    const bgfx::Caps* caps = bgfx::getCaps();
    std::cout << "Pipeline: BGFX renderer: " << caps->rendererType << std::endl;
    std::cout << "Pipeline: BGFX vendor: " << caps->vendorId << std::endl;

    // Fixed view matrix (top-down view)
    glm::mat4 m_ViewMatrix = glm::lookAt(
        glm::vec3(0.0f, 10.0f, 0.0f),  // Camera position (above)
        glm::vec3(0.0f, 0.0f, 0.0f),   // Look at origin
        glm::vec3(0.0f, 0.0f, 1.0f)    // Up direction
    );
    // Fixed projection matrix
    glm::mat4 m_ProjectionMatrix = glm::perspective(
        glm::radians(45.0f),           // FOV
        static_cast<float>(width) / height,  // Aspect ratio
        0.1f, 100.0f                   // Near and far planes
    );
    
    std::cout << "Pipeline: Fixed view setup completed" << std::endl;

    bgfx::setViewTransform(0, &m_ViewMatrix[0][0], &m_ProjectionMatrix[0][0]);
    bgfx::setViewRect(0, 0, 0, width, height); // To be replaced later

    bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , 0x303030ff
        , 1.0f
        , 0
        );
    
    m_BGFXInitialized = true;
    
    std::cout << "Pipeline: BGFX initialized successfully" << std::endl;
}

void Pipeline::AddStage(std::unique_ptr<PipelineStage> stage) {
    if (!stage) return;

    const std::string& name = stage->GetName();
    m_StageMap[name] = stage.get();
    m_Stages.push_back(std::move(stage));

    std::cout << "Pipeline: Added stage '" << name << "'" << std::endl;
}

void Pipeline::RemoveStage(const std::string& name) {
    auto it = m_StageMap.find(name);
    if (it != m_StageMap.end()) {
        // Remove from vector
        m_Stages.erase(
            std::remove_if(m_Stages.begin(), m_Stages.end(),
                           [&name](const StagePtr& stage) { return stage->GetName() == name; }),
            m_Stages.end());

        // Remove from map
        m_StageMap.erase(it);

        std::cout << "Pipeline: Removed stage '" << name << "'" << std::endl;
    }
}

void Pipeline::EnableStage(const std::string& name, bool enabled) {
    auto it = m_StageMap.find(name);
    if (it != m_StageMap.end()) {
        it->second->SetEnabled(enabled);
        std::cout << "Pipeline: " << (enabled ? "Enabled" : "Disabled") << " stage '" << name << "'"
                  << std::endl;
    }
}

void Pipeline::Execute() {
    if (!m_BGFXInitialized) {
        std::cout << "Pipeline: BGFX not initialized" << std::endl;
        return;
    }

    // Count enabled stages
    int enabledCount = 0;
    for (const auto& stage : m_Stages) {
        if (stage->IsEnabled()) {
            enabledCount++;
        }
    }

    std::cout << "Pipeline: Executing " << enabledCount << " stages" << std::endl;

    for (auto& stage : m_Stages) {
        if (stage->IsEnabled()) {
            std::cout << "Pipeline: Executing stage '" << stage->GetName() << "'" << std::endl;
            stage->Execute(*this);
        }
    }
    
    // Submit render frame
    bgfx::frame();
}

PipelineStage* Pipeline::GetStage(const std::string& name) {
    auto it = m_StageMap.find(name);
    return (it != m_StageMap.end()) ? it->second : nullptr;
}

}  // namespace Rendering
}  // namespace Boids