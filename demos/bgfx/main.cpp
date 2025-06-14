#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

int main(int argc, char** argv)
{
    // Verify header files are correctly included
    bgfx::Init init;
    init.type = bgfx::RendererType::Count; // Auto-select renderer
    init.resolution.width = 1280;
    init.resolution.height = 720;
    
    return 0;
} 