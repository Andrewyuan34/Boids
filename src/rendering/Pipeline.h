// src/rendering/Pipeline.h
#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "PipelineStage.h"

namespace Boids {
namespace Rendering {

class Pipeline {
   public:
    struct Options {
        bool triangles = false;
        bool texture = false;
        bool vertices = false;

        void Reset() {
            triangles = false;
            texture = false;
            vertices = false;
        }
    };

    Pipeline();
    ~Pipeline();

    void AddStage(std::unique_ptr<PipelineStage> stage);
    void RemoveStage(const std::string& name);
    void EnableStage(const std::string& name, bool enabled);

    void Execute();

    Options& GetOptions() { return m_Options; }
    const Options& GetOptions() const { return m_Options; }

    PipelineStage* GetStage(const std::string& name);

   private:
    std::vector<StagePtr> m_Stages;
    std::unordered_map<std::string, PipelineStage*> m_StageMap;
    Options m_Options;
};

}  // namespace Rendering
}  // namespace Boids