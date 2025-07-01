#include "InitializeStage.h"
#include "../Pipeline.h"
#include <iostream>
#include <cassert>
#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>

// Disable DirectX shaders on Linux (following openblack's approach)
#if BX_PLATFORM_LINUX
#undef BGFX_EMBEDDED_SHADER_DXBC
#define BGFX_EMBEDDED_SHADER_DXBC(...)
#undef BGFX_EMBEDDED_SHADER_DX9BC
#define BGFX_EMBEDDED_SHADER_DX9BC(...)
#endif

// Include generated shader headers
#define SHADER_NAME vs_simple
#include "ShaderIncluder.h"
#define SHADER_NAME fs_simple
#include "ShaderIncluder.h"

// Define embedded shader array
static const bgfx::EmbeddedShader s_embeddedShaders[] = {
    BGFX_EMBEDDED_SHADER(vs_simple), BGFX_EMBEDDED_SHADER(fs_simple), BGFX_EMBEDDED_SHADER_END()};

namespace Boids {
namespace Rendering {

InitializeStage::InitializeStage() : PipelineStage("Initialize") {}

InitializeStage::~InitializeStage() = default;

void InitializeStage::Execute(Pipeline& pipeline) {
    if (!m_Enabled) return;

    if (!m_Initialized) {
        SetupBGFX();
        m_Initialized = true;
        std::cout << "InitializeStage: BGFX setup completed" << std::endl;
    }
}

void InitializeStage::OnAttach() {
    std::cout << "InitializeStage: Attached to pipeline" << std::endl;
}

void InitializeStage::OnDetach() {
    std::cout << "InitializeStage: Detached from pipeline" << std::endl;
}

void InitializeStage::SetupBGFX() {
    // Create shader program using embedded shaders
    bgfx::RendererType::Enum type = bgfx::getRendererType();

    // Create vertex shader
    bgfx::ShaderHandle vsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_simple");
    assert(bgfx::isValid(vsh));

    // Create fragment shader
    bgfx::ShaderHandle fsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_simple");
    assert(bgfx::isValid(fsh));

    // Create shader program
    m_Program = bgfx::createProgram(vsh, fsh, true);
    std::cout << "InitializeStage: BGFX shader setup completed" << std::endl;
}

}  // namespace Rendering
}  // namespace Boids