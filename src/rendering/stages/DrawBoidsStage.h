#pragma once
#include "../PipelineStage.h"
#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

namespace Boids {
namespace Rendering {

class DrawBoidsStage : public PipelineStage {
   public:
    DrawBoidsStage();
    ~DrawBoidsStage() override;

    void Execute(Pipeline& pipeline) override;
    void OnAttach() override;
    void OnDetach() override;

   private:
    void SetupBGFX();
    void RenderBoid(const glm::vec3& position, const glm::vec3& velocity);

    bgfx::VertexBufferHandle m_VertexBuffer = BGFX_INVALID_HANDLE;
    bgfx::IndexBufferHandle m_IndexBuffer = BGFX_INVALID_HANDLE;
    bgfx::ProgramHandle m_Program = BGFX_INVALID_HANDLE;
    bool m_Initialized = false;
};

}  // namespace Rendering
}  // namespace Boids