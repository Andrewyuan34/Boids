#define GLM_ENABLE_EXPERIMENTAL
#include "BoidManager.h"
#include <glm/gtx/norm.hpp>

namespace Boids {

BoidManager::BoidManager() = default;
BoidManager::~BoidManager() = default;

void BoidManager::initialize(const BoidsParams& params) {
    m_Boids.clear();
    for (int i = 0; i < params.boidCount; ++i) {
        float x = (static_cast<float>(rand()) / RAND_MAX  * 2.0f - 1.0f) / 50.0f;
        float y = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) / 50.0f;
        glm::vec2 pos(x, y);
        float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
        glm::vec2 vel(cos(angle) / 50.0f, sin(angle) / 50.0f);
        m_Boids.push_back(std::make_unique<Boid>(pos, vel));
    }
}

void BoidManager::update(float deltaTime, const BoidsParams& params) {
    for (auto& boid : m_Boids) {
        glm::vec2 separation(0.0f);
        glm::vec2 alignment(0.0f);
        glm::vec2 cohesion(0.0f);

        int separationCount = 0, alignmentCount = 0, cohesionCount = 0;
        glm::vec2 pos = boid->getPosition();
        glm::vec2 vel = boid->getVelocity();

        for (const auto& other : m_Boids) {
            if (boid.get() == other.get()) continue;
            glm::vec2 diff = other->getPosition() - pos;
            float dist2 = glm::length2(diff); // faster than length for comparisons

            // Separation
            if (dist2 < params.separationRadius * params.separationRadius && dist2 > 0.0f) {
                separation -= (other->getPosition() - pos) / std::sqrt(dist2);
                separationCount++;
            }
            // Alignment
            if (dist2 < params.alignmentRadius * params.alignmentRadius) {
                alignment += other->getVelocity();
                alignmentCount++;
            }
            // Cohesion
            if (dist2 < params.cohesionRadius * params.cohesionRadius) {
                cohesion += other->getPosition();
                cohesionCount++;
            }
        }

        // Normalize and weight
        if (separationCount > 0) {
            separation /= (float)separationCount;
            if (glm::length(separation) > 0.0f)
                separation = glm::normalize(separation) * params.maxSpeed - vel;
            if (glm::length(separation) > params.maxForce)
                separation = glm::normalize(separation) * params.maxForce;
        }
        if (alignmentCount > 0) {
            alignment /= (float)alignmentCount;
            if (glm::length(alignment) > 0.0f)
                alignment = glm::normalize(alignment) * params.maxSpeed - vel;
            if (glm::length(alignment) > params.maxForce)
                alignment = glm::normalize(alignment) * params.maxForce;
        }
        if (cohesionCount > 0) {
            cohesion /= (float)cohesionCount;
            cohesion = cohesion - pos;
            if (glm::length(cohesion) > 0.0f)
                cohesion = glm::normalize(cohesion) * params.maxSpeed - vel;
            if (glm::length(cohesion) > params.maxForce)
                cohesion = glm::normalize(cohesion) * params.maxForce;
        }

        glm::vec2 steering =
            params.separationWeight * separation +
            params.alignmentWeight * alignment +
            params.cohesionWeight * cohesion;

        boid->applyForce(steering);
    }

    // Update all Boid positions and velocities
    for (auto& boid : m_Boids) {
        boid->update(deltaTime, params);
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