#include "Simulation.h"

namespace Boids {

Simulation::Simulation() = default;
Simulation::~Simulation() = default;

void Simulation::initialize() { m_BoidManager.initialize(BoidsParams::get()); }

void Simulation::update(float deltaTime) { m_BoidManager.update(deltaTime, BoidsParams::get()); }

void Simulation::render() const { m_BoidManager.render(); }

BoidManager& Simulation::getBoidManager() { return m_BoidManager; }

}  // namespace Boids