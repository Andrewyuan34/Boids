#pragma once
#include "../PipelineStage.h"
#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    
    void SetupBGFX();
    
    bool m_Initialized = false;
    bgfx::ProgramHandle m_Program = BGFX_INVALID_HANDLE;

};

}  // namespace Rendering
}  // namespace Boids