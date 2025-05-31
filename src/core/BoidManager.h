#pragma once
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <vector>
#include <memory>
#include "Boid.h"
#include "ui/BoidsParams.h"

namespace Boids {

class BoidManager {
public:
    BoidManager();
    ~BoidManager();

    void initialize(const BoidsParams& params);
    void update(float deltaTime, const BoidsParams& params);
    void render() const;
    glm::vec3 computeSeparation(const Boid& boid, const BoidsParams& params) const;
    glm::vec3 computeAlignment(const Boid& boid, const BoidsParams& params) const;
    glm::vec3 computeCohesion(const Boid& boid, const BoidsParams& params) const;
    glm::vec3 computeBoundaryForce(const glm::vec3& pos, float boundaryMin, float boundaryMax, float buffer, float maxForce) const;

    const std::vector<std::unique_ptr<Boid>>& getBoids() const;

private:
    std::vector<std::unique_ptr<Boid>> m_Boids;
};

} // namespace Boids