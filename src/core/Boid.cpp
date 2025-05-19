#include "Boid.h"
#include <GLFW/glfw3.h>

namespace Boids {

Boid::Boid(const glm::vec2& position, const glm::vec2& velocity)
    : m_Position(position), m_Velocity(velocity) {}

glm::vec2 Boid::getPosition() const { return m_Position; }
glm::vec2 Boid::getVelocity() const { return m_Velocity; }

void Boid::setPosition(const glm::vec2& pos) { m_Position = pos; }
void Boid::setVelocity(const glm::vec2& vel) { m_Velocity = vel; }

void Boid::applyForce(const glm::vec2& force) {
    m_Acceleration += force;
}

void Boid::update(float deltaTime, const BoidsParams& params) {
    m_Velocity += m_Acceleration;
    if (glm::length(m_Velocity) > params.maxSpeed)
        m_Velocity = glm::normalize(m_Velocity) * params.maxSpeed;
    m_Position += m_Velocity * deltaTime;
    m_Acceleration = glm::vec2(0.0f); // Reset acceleration for next frame
}

void Boid::render() const {
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(m_Position.x, m_Position.y);
    glEnd();
}

} // namespace Boids