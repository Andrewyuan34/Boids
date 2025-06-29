// src/rendering/PipelineStage.h
#pragma once
#include <string>
#include <memory>

namespace Boids {
namespace Rendering {

class Pipeline;  // forward declaration

class PipelineStage {
   public:
    PipelineStage(const std::string& name);
    virtual ~PipelineStage() = default;

    virtual void Execute(Pipeline& pipeline) = 0;

    virtual void OnAttach() {}
    virtual void OnDetach() {}

    void SetEnabled(bool enabled) { m_Enabled = enabled; }
    bool IsEnabled() const { return m_Enabled; }
    const std::string& GetName() const { return m_Name; }

   protected:
    std::string m_Name;
    bool m_Enabled = true;
};

using StagePtr = std::unique_ptr<PipelineStage>;

}  // namespace Rendering
}  // namespace Boids