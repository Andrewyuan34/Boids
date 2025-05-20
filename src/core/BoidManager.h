#pragma once
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
    glm::vec2 computeSeparation(const Boid& boid, const BoidsParams& params) const;
    glm::vec2 computeAlignment(const Boid& boid, const BoidsParams& params) const;
    glm::vec2 computeCohesion(const Boid& boid, const BoidsParams& params) const;


    const std::vector<std::unique_ptr<Boid>>& getBoids() const;

private:
    std::vector<std::unique_ptr<Boid>> m_Boids;
};

} // namespace Boids