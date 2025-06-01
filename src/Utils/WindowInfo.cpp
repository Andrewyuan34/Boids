#include "WindowInfo.h"

void WindowInfo::resize(int width, int height) {
    m_Width = width;
    m_Height = height;
}

glm::vec2 WindowInfo::screenToWorld(const glm::vec2& screenPos) const {
    // Convert screen coordinates (0 to width/height) to world coordinates (-1 to 1)
    return glm::vec2((2.0f * screenPos.x / m_Width) - 1.0f, 1.0f - (2.0f * screenPos.y / m_Height));
}

glm::vec2 WindowInfo::worldToScreen(const glm::vec2& worldPos) const {
    // Convert world coordinates (-1 to 1) to screen coordinates (0 to width/height)
    return glm::vec2(((worldPos.x + 1.0f) * m_Width) / 2.0f,
                     ((1.0f - worldPos.y) * m_Height) / 2.0f);
}