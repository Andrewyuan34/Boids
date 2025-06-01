#pragma once

#include <glm/glm.hpp>

class WindowInfo {
public:
    WindowInfo() = default;
    ~WindowInfo() = default;

    // Window dimensions
    int getWidth() const { return m_Width; }
    int getHeight() const { return m_Height; }
    void resize(int width, int height);

    // Coordinate transformations
    glm::vec2 screenToWorld(const glm::vec2& screenPos) const;
    glm::vec2 worldToScreen(const glm::vec2& worldPos) const;

private:
    int m_Width = 0;
    int m_Height = 0;
}; 