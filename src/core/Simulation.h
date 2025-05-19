#pragma once
#include "BoidManager.h"
#include "ui/BoidsParams.h"

namespace Boids {

class Simulation {
public:
    Simulation();
    ~Simulation();

    void initialize(const BoidsParams& params);
    void update(float deltaTime, const BoidsParams& params);
    void render() const;

    BoidManager& getBoidManager();

private:
    BoidManager m_BoidManager;
};

} // namespace Boids