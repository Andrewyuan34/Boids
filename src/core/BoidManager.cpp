#define GLM_ENABLE_EXPERIMENTAL
#include "BoidManager.h"
#include <glm/gtx/norm.hpp>

namespace Boids {

BoidManager::BoidManager() = default;
BoidManager::~BoidManager() = default;

void BoidManager::initialize(const BoidsParams& params) {
    m_Boids.clear();
    for (int i = 0; i < params.boidCount; ++i) {
        float x = (static_cast<float>(rand()) / RAND_MAX  * 2.0f - 1.0f) / 10.0f;
        float y = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) / 10.0f;
        glm::vec2 pos(x, y);
        float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
        glm::vec2 vel(cos(angle) / 50.0f, sin(angle) / 50.0f);
        m_Boids.push_back(std::make_unique<Boid>(pos, vel));
    }
}

void BoidManager::update(float deltaTime, const BoidsParams& params) {
    for (auto& boid : m_Boids) {
        glm::vec2 separation = computeSeparation(*boid, params);
        glm::vec2 alignment  = computeAlignment(*boid, params);
        glm::vec2 cohesion   = computeCohesion(*boid, params);
        glm::vec2 boundaryForce = computeBoundaryForce(boid->getPosition(), params.boundaryMin, params.boundaryMax, 0.2f, params.boundaryForceMax);

        glm::vec2 steering =
            params.separationWeight * separation +
            params.alignmentWeight * alignment +
            params.cohesionWeight * cohesion +
            boundaryForce * params.boundaryWeight;

        boid->applyForce(steering);
    }

    for (auto& boid : m_Boids) {
        boid->update(deltaTime, params);
    }
}

glm::vec2 BoidManager::computeSeparation(const Boid& boid, const BoidsParams& params) const {
    glm::vec2 force(0.0f);
    int count = 0;
    glm::vec2 pos = boid.getPosition();

    for (const auto& other : m_Boids) {
        if (&boid == other.get()) continue;
        glm::vec2 diff = other->getPosition() - pos;
        float dist2 = glm::length2(diff);
        if (dist2 < params.separationRadius * params.separationRadius && dist2 > 0.0f) {
            force -= (other->getPosition() - pos) / std::sqrt(dist2);
            count++;
        }
    }
    if (count > 0) {
        force /= (float)count;
        if (glm::length(force) > 0.0f)
            force = glm::normalize(force) * params.maxSpeed - boid.getVelocity();
        if (glm::length(force) > params.maxForce)
            force = glm::normalize(force) * params.maxForce;
    }
    return force;
}

glm::vec2 BoidManager::computeAlignment(const Boid& boid, const BoidsParams& params) const {
    glm::vec2 avgVelocity(0.0f);
    int count = 0;
    glm::vec2 pos = boid.getPosition();

    for (const auto& other : m_Boids) {
        if (&boid == other.get()) continue;
        glm::vec2 diff = other->getPosition() - pos;
        float dist2 = glm::length2(diff);
        if (dist2 < params.alignmentRadius * params.alignmentRadius) {
            avgVelocity += other->getVelocity();
            count++;
        }
    }
    if (count > 0) {
        avgVelocity /= (float)count;
        if (glm::length(avgVelocity) > 0.0f)
            avgVelocity = glm::normalize(avgVelocity) * params.maxSpeed - boid.getVelocity();
        if (glm::length(avgVelocity) > params.maxForce)
            avgVelocity = glm::normalize(avgVelocity) * params.maxForce;
    }
    return avgVelocity;
}

glm::vec2 BoidManager::computeCohesion(const Boid& boid, const BoidsParams& params) const {
    glm::vec2 center(0.0f);
    int count = 0;
    glm::vec2 pos = boid.getPosition();

    for (const auto& other : m_Boids) {
        if (&boid == other.get()) continue;
        glm::vec2 diff = other->getPosition() - pos;
        float dist2 = glm::length2(diff);
        if (dist2 < params.cohesionRadius * params.cohesionRadius) {
            center += other->getPosition();
            count++;
        }
    }
    if (count > 0) {
        center /= (float)count;
        glm::vec2 desired = center - pos;
        if (glm::length(desired) > 0.0f)
            desired = glm::normalize(desired) * params.maxSpeed - boid.getVelocity();
        if (glm::length(desired) > params.maxForce)
            desired = glm::normalize(desired) * params.maxForce;
        return desired;
    }
    return glm::vec2(0.0f);
}

glm::vec2 BoidManager::computeBoundaryForce(const glm::vec2& pos, float boundaryMin, float boundaryMax, float buffer, float maxForce) const {
    glm::vec2 force(0.0f);

    if (pos.x < boundaryMin + buffer) {
        float dist = boundaryMin + buffer - pos.x;
        force.x += (dist / buffer) * maxForce;
    } else if (pos.x > boundaryMax - buffer) {
        float dist = pos.x - (boundaryMax - buffer);
        force.x -= (dist / buffer) * maxForce;
    }

    if (pos.y < boundaryMin + buffer) {
        float dist = boundaryMin + buffer - pos.y;
        force.y += (dist / buffer) * maxForce;
    } else if (pos.y > boundaryMax - buffer) {
        float dist = pos.y - (boundaryMax - buffer);
        force.y -= (dist / buffer) * maxForce;
    }

    return force;
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