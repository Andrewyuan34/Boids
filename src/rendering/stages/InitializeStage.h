#pragma once
#include "../PipelineStage.h"
#include <bgfx/bgfx.h>

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
    bgfx::ProgramHandle m_Program = BGFX_INVALID_HANDLE;
    void SetupBGFX();
};

}  // namespace Rendering
}  // namespace Boids