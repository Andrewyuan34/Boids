#include "BoidManager.h"
#include <glm/gtx/norm.hpp>
#include <random>

namespace Boids {

BoidManager::BoidManager() = default;
BoidManager::~BoidManager() = default;

void BoidManager::initialize(const BoidsParams& params) {
    m_Boids.clear();

    // Create random number engine and distribution
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> pos_dist(-0.1f, 0.1f);
    std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> height_dist(-0.1f, 0.1f);

    // Generate boids info
    for (int i = 0; i < params.boidCount; ++i) {
        float x = pos_dist(rng);
        float y = pos_dist(rng);
        float z = height_dist(rng);  
        glm::vec3 pos(x, y, z);

        float angle = angle_dist(rng);
        float speed = 1.0f / 50.0f;  
        glm::vec3 vel(
            std::cos(angle) * speed,
            std::sin(angle) * speed,
            height_dist(rng) * speed  
        );

        m_Boids.push_back(std::make_unique<Boid>(pos, vel));
    }
}

void BoidManager::update(float deltaTime, const BoidsParams& params) {
    for (auto& boid : m_Boids) {
        glm::vec3 separation = computeSeparation(*boid, params);
        glm::vec3 alignment  = computeAlignment(*boid, params);
        glm::vec3 cohesion   = computeCohesion(*boid, params);
        glm::vec3 boundaryForce = computeBoundaryForce(boid->getPosition(), params.boundaryMin, params.boundaryMax, 0.2f, params.boundaryForceMax);

        glm::vec3 steering =
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

glm::vec3 BoidManager::computeSeparation(const Boid& boid, const BoidsParams& params) const {
    glm::vec3 force(0.0f);
    int count = 0;
    glm::vec3 pos = boid.getPosition();

    for (const auto& other : m_Boids) {
        if (&boid == other.get()) continue;
        glm::vec3 diff = other->getPosition() - pos;
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

glm::vec3 BoidManager::computeAlignment(const Boid& boid, const BoidsParams& params) const {
    glm::vec3 avgVelocity(0.0f);
    int count = 0;
    glm::vec3 pos = boid.getPosition();

    for (const auto& other : m_Boids) {
        if (&boid == other.get()) continue;
        glm::vec3 diff = other->getPosition() - pos;
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

glm::vec3 BoidManager::computeCohesion(const Boid& boid, const BoidsParams& params) const {
    glm::vec3 center(0.0f);
    int count = 0;
    glm::vec3 pos = boid.getPosition();

    for (const auto& other : m_Boids) {
        if (&boid == other.get()) continue;
        glm::vec3 diff = other->getPosition() - pos;
        float dist2 = glm::length2(diff);
        if (dist2 < params.cohesionRadius * params.cohesionRadius) {
            center += other->getPosition();
            count++;
        }
    }
    if (count > 0) {
        center /= (float)count;
        glm::vec3 desired = center - pos;
        if (glm::length(desired) > 0.0f)
            desired = glm::normalize(desired) * params.maxSpeed - boid.getVelocity();
        if (glm::length(desired) > params.maxForce)
            desired = glm::normalize(desired) * params.maxForce;
        return desired;
    }
    return glm::vec3(0.0f);
}

glm::vec3 BoidManager::computeBoundaryForce(const glm::vec3& pos, float boundaryMin, float boundaryMax, float buffer, float maxForce) const {
    glm::vec3 force(0.0f);

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

    if (pos.z < boundaryMin + buffer) {
        float dist = boundaryMin + buffer - pos.z;
        force.z += (dist / buffer) * maxForce;
    } else if (pos.z > boundaryMax - buffer) {
        float dist = pos.z - (boundaryMax - buffer);
        force.z -= (dist / buffer) * maxForce;
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