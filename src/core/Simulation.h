#pragma once
#include "BoidManager.h"
#include "ui/BoidsParams.h"

// To be extended to handle more entities later
namespace Boids {  // to be removed

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

}  // namespace Boids