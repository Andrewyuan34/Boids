#include "PipelineStage.h"

namespace Boids {
namespace Rendering {

PipelineStage::PipelineStage(const std::string& name) : m_Name(name), m_Enabled(true) {}

}  // namespace Rendering
}  // namespace Boids