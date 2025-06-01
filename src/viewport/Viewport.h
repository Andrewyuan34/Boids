// src/core/Viewport.h
#pragma once
#include <glm/glm.hpp>

class Viewport {
   public:
    Viewport(int width, int height, float simMinX, float simMaxX, float simMinY, float simMaxY);

    Viewport() = default;

    // Update window size
    void resize(int newWidth, int newHeight);

    // Getters
    int getWidth() const;
    int getHeight() const;
    float getSimMinX() const;
    float getSimMaxX() const;
    float getSimMinY() const;
    float getSimMaxY() const;

    // Mapping between window (pixel) and simulation (world) space
    glm::vec2 windowToSim(const glm::vec2& windowPos) const;
    glm::vec2 simToWindow(const glm::vec2& simPos) const;

   private:
    int m_Width, m_Height;
    float m_SimMinX, m_SimMaxX, m_SimMinY, m_SimMaxY;
};