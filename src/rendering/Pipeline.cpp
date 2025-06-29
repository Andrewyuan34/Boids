#include "Pipeline.h"
#include <algorithm>
#include <iostream>

// TODO: use logger instead of cout

namespace Boids {
namespace Rendering {

Pipeline::Pipeline() = default;

Pipeline::~Pipeline() = default;

void Pipeline::AddStage(std::unique_ptr<PipelineStage> stage) {
    if (!stage) return;

    const std::string& name = stage->GetName();
    m_StageMap[name] = stage.get();
    m_Stages.push_back(std::move(stage));

    std::cout << "Pipeline: Added stage '" << name << "'" << std::endl;
}

void Pipeline::RemoveStage(const std::string& name) {
    auto it = m_StageMap.find(name);
    if (it != m_StageMap.end()) {
        // Remove from vector
        m_Stages.erase(
            std::remove_if(m_Stages.begin(), m_Stages.end(),
                           [&name](const StagePtr& stage) { return stage->GetName() == name; }),
            m_Stages.end());

        // Remove from map
        m_StageMap.erase(it);

        std::cout << "Pipeline: Removed stage '" << name << "'" << std::endl;
    }
}

void Pipeline::EnableStage(const std::string& name, bool enabled) {
    auto it = m_StageMap.find(name);
    if (it != m_StageMap.end()) {
        it->second->SetEnabled(enabled);
        std::cout << "Pipeline: " << (enabled ? "Enabled" : "Disabled") << " stage '" << name << "'"
                  << std::endl;
    }
}

void Pipeline::Execute() {
    // Count enabled stages
    int enabledCount = 0;
    for (const auto& stage : m_Stages) {
        if (stage->IsEnabled()) {
            enabledCount++;
        }
    }

    std::cout << "Pipeline: Executing " << enabledCount << " stages" << std::endl;

    for (auto& stage : m_Stages) {
        if (stage->IsEnabled()) {
            std::cout << "Pipeline: Executing stage '" << stage->GetName() << "'" << std::endl;
            stage->Execute(*this);
        }
    }
}

PipelineStage* Pipeline::GetStage(const std::string& name) {
    auto it = m_StageMap.find(name);
    return (it != m_StageMap.end()) ? it->second : nullptr;
}

}  // namespace Rendering
}  // namespace Boids