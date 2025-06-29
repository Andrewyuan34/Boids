#include "InitializeStage.h"
#include "../Pipeline.h"
#include <iostream>

namespace Boids {
namespace Rendering {

InitializeStage::InitializeStage() : PipelineStage("Initialize") {}

InitializeStage::~InitializeStage() = default;

void InitializeStage::Execute(Pipeline& pipeline) {
    if (!m_Enabled) return;

    if (!m_Initialized) {
        SetupBGFX();
        m_Initialized = true;
        std::cout << "InitializeStage: BGFX setup completed" << std::endl;
    }
}

void InitializeStage::OnAttach() {
    std::cout << "InitializeStage: Attached to pipeline" << std::endl;
}

void InitializeStage::OnDetach() {
    std::cout << "InitializeStage: Detached from pipeline" << std::endl;
}

void InitializeStage::SetupBGFX() {
    // TODO: Implement BGFX setup
    std::cout << "InitializeStage: Setting up BGFX..." << std::endl;
}

}  // namespace Rendering
}  // namespace Boids