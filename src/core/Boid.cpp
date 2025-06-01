#include "Boid.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Boids {

Boid::Boid(const glm::vec3& position, const glm::vec3& velocity)
    : m_Position(position), m_Velocity(velocity), m_Acceleration(0.0f) {
    // Initialize rotation to face velocity direction
    if (glm::length(velocity) > 0.0f) {
        m_Rotation = glm::quatLookAt(glm::normalize(velocity), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    m_Scale = glm::vec3(0.1f);  // Set a default scale
}

glm::vec3 Boid::getPosition() const { return m_Position; }
glm::vec3 Boid::getVelocity() const { return m_Velocity; }

void Boid::setPosition(const glm::vec3& pos) { m_Position = pos; }
void Boid::setVelocity(const glm::vec3& vel) { m_Velocity = vel; }

void Boid::applyForce(const glm::vec3& force) { m_Acceleration += force; }

void Boid::update(float deltaTime, const BoidsParams& params) {
    m_Velocity += m_Acceleration;
    if (glm::length(m_Velocity) > params.maxSpeed)
        m_Velocity = glm::normalize(m_Velocity) * params.maxSpeed;
    m_Position += m_Velocity * deltaTime;
    m_Acceleration = glm::vec3(0.0f);  // Reset acceleration for next frame
}

void Boid::render() const {
    // For now, just render a simple triangle
    glBegin(GL_TRIANGLES);
    // Set color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw a triangle
    glVertex3f(m_Position.x, m_Position.y, m_Position.z);
    glVertex3f(m_Position.x + 0.1f, m_Position.y - 0.1f, m_Position.z);
    glVertex3f(m_Position.x - 0.1f, m_Position.y - 0.1f, m_Position.z);
    glEnd();
}

}  // namespace Boids