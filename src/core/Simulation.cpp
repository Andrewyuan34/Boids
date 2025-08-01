#include "Simulation.h"
#include "rendering/stages/InitializeStage.h"

namespace Boids {

Simulation::Simulation() = default;
Simulation::~Simulation() = default;

void Simulation::initialize(GLFWwindow* window, int width, int height) { 
    m_BoidManager.initialize(BoidsParams::get()); 
    m_RenderPipeline.Initialize(window, width, height);
    m_RenderPipeline.AddStage(std::make_unique<Rendering::InitializeStage>());
}

void Simulation::update(float deltaTime) { m_BoidManager.update(deltaTime, BoidsParams::get()); }

void Simulation::render() {
    // TODO: add new render logic
    //m_RenderPipeline.Execute(); // Commented out for now
    m_BoidManager.render();
}

BoidManager& Simulation::getBoidManager() { return m_BoidManager; }

}  // namespace Boids