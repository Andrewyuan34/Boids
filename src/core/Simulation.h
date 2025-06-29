#pragma once
#include "BoidManager.h"
#include "ui/BoidsParams.h"
#include "rendering/Pipeline.h"

// To be extended to handle more entities later
namespace Boids {  // to be removed

class Simulation {
   public:
    Simulation();
    ~Simulation();

    void initialize();
    void update(float deltaTime);
    void render();

    BoidManager& getBoidManager();
    Rendering::Pipeline& getRenderPipeline() { return m_RenderPipeline; }

    const BoidsParams& getParams() const { return m_Params; }
    void setParams(const BoidsParams& params) { m_Params = params; }

   private:
    BoidManager m_BoidManager;
    BoidsParams m_Params;
    Rendering::Pipeline m_RenderPipeline;
};

}  // namespace Boids