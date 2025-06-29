#include "Log.h"

namespace Log {
static std::shared_ptr<spdlog::logger> s_Logger;

void Init() {
    if (!s_Logger) {
        s_Logger = spdlog::stdout_color_mt("Boids");
        s_Logger->set_level(spdlog::level::trace);
    }
}

std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
}  // namespace Log
