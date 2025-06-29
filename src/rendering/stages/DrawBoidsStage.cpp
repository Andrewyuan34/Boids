#include "DrawBoidsStage.h"
#include "../Pipeline.h"
#include <iostream>

namespace Boids {
namespace Rendering {

DrawBoidsStage::DrawBoidsStage() : PipelineStage("DrawBoids") {}

DrawBoidsStage::~DrawBoidsStage() = default;

void DrawBoidsStage::Execute(Pipeline& pipeline) {
    if (!m_Enabled) return;

    if (!m_Initialized) {
        SetupBGFX();
        m_Initialized = true;
    }

    std::cout << "DrawBoidsStage: Rendering boids..." << std::endl;

    const auto& options = pipeline.GetOptions();
    std::cout << "DrawBoidsStage: triangles=" << options.triangles
              << ", texture=" << options.texture << ", vertices=" << options.vertices << std::endl;
}

void DrawBoidsStage::OnAttach() {
    std::cout << "DrawBoidsStage: Attached to pipeline" << std::endl;
}

void DrawBoidsStage::OnDetach() {
    std::cout << "DrawBoidsStage: Detached from pipeline" << std::endl;
}

void DrawBoidsStage::SetupBGFX() {
    std::cout << "DrawBoidsStage: Setting up BGFX resources..." << std::endl;
}

void DrawBoidsStage::RenderBoid(const glm::vec3& position, const glm::vec3& velocity) {
    std::cout << "DrawBoidsStage: Rendering boid at (" << position.x << ", " << position.y << ", "
              << position.z << ")" << std::endl;
}

}  // namespace Rendering
}  // namespace Boids