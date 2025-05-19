#include "Simulation.h"

namespace Boids {

Simulation::Simulation() = default;
Simulation::~Simulation() = default;

void Simulation::initialize(const BoidsParams& params) {
    m_BoidManager.initialize(params);
}

void Simulation::update(float deltaTime, const BoidsParams& params) {
    m_BoidManager.update(deltaTime, params);
}

void Simulation::render() const {
    m_BoidManager.render();
}

BoidManager& Simulation::getBoidManager() {
    return m_BoidManager;
}

} // namespace Boids