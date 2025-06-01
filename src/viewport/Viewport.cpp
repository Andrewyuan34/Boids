// src/core/Viewport.cpp
#include "Viewport.h"

Viewport::Viewport(int width, int height, float simMinX, float simMaxX, float simMinY,
                   float simMaxY)
    : m_Width(width),
      m_Height(height),
      m_SimMinX(simMinX),
      m_SimMaxX(simMaxX),
      m_SimMinY(simMinY),
      m_SimMaxY(simMaxY) {}

void Viewport::resize(int newWidth, int newHeight) {
    m_Width = newWidth;
    m_Height = newHeight;
    // TODO: Update the m_SimMinX, m_SimMaxX, m_SimMinY, m_SimMaxY
}

int Viewport::getWidth() const { return m_Width; }
int Viewport::getHeight() const { return m_Height; }
float Viewport::getSimMinX() const { return m_SimMinX; }
float Viewport::getSimMaxX() const { return m_SimMaxX; }
float Viewport::getSimMinY() const { return m_SimMinY; }
float Viewport::getSimMaxY() const { return m_SimMaxY; }

glm::vec2 Viewport::windowToSim(const glm::vec2& windowPos) const {
    float x = m_SimMinX + (windowPos.x / m_Width) * (m_SimMaxX - m_SimMinX);
    float y = m_SimMinY +
              (1.0f - windowPos.y / m_Height) * (m_SimMaxY - m_SimMinY);  // y axis is reversed
    return glm::vec2(x, y);
}

glm::vec2 Viewport::simToWindow(const glm::vec2& simPos) const {
    float x = (simPos.x - m_SimMinX) / (m_SimMaxX - m_SimMinX) * m_Width;
    float y =
        (1.0f - (simPos.y - m_SimMinY) / (m_SimMaxY - m_SimMinY)) * m_Height;  // y axis is reversed
    return glm::vec2(x, y);
}