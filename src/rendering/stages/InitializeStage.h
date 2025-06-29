#pragma once
#include "../PipelineStage.h"

namespace Boids {
namespace Rendering {

class InitializeStage : public PipelineStage {
   public:
    InitializeStage();
    ~InitializeStage() override;

    void Execute(Pipeline& pipeline) override;
    void OnAttach() override;
    void OnDetach() override;

   private:
    bool m_Initialized = false;
    void SetupBGFX();
};

}  // namespace Rendering
}  // namespace Boids