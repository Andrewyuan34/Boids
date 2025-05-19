#include "BoidManager.h"

namespace Boids {

BoidManager::BoidManager() = default;
BoidManager::~BoidManager() = default;

void BoidManager::initialize(const BoidsParams& params) {
    m_Boids.clear();
    for (int i = 0; i < params.boidCount; ++i) {
        // TODO: randomize position and velocity
        m_Boids.push_back(std::make_unique<Boid>(glm::vec2(0,0), glm::vec2(1,0)));
    }
}

void BoidManager::update(float deltaTime, const BoidsParams& params) {
    for (auto& boid : m_Boids) {
        boid->update(deltaTime);
        // TODO: implement Boids behavior later
    }
}

void BoidManager::render() const {
    for (const auto& boid : m_Boids) {
        boid->render();
    }
}

const std::vector<std::unique_ptr<Boid>>& BoidManager::getBoids() const {
    return m_Boids;
}

} // namespace Boids