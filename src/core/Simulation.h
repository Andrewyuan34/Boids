#pragma once
#include "BoidManager.h"
#include "ui/BoidsParams.h"

// To be extended to handle more entities later
namespace Boids {  // to be removed

class Simulation {
   public:
    Simulation();
    ~Simulation();

    void initialize();
    void update(float deltaTime);
    void render() const;

    BoidManager& getBoidManager();

    const BoidsParams& getParams() const { return m_Params; }
    void setParams(const BoidsParams& params) { m_Params = params; }

   private:
    BoidManager m_BoidManager;
    BoidsParams m_Params;
};

}  // namespace Boids