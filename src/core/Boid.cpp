#include "Boid.h"

namespace Boids {

Boid::Boid(const glm::vec2& position, const glm::vec2& velocity)
    : m_Position(position), m_Velocity(velocity) {}

glm::vec2 Boid::getPosition() const { return m_Position; }
glm::vec2 Boid::getVelocity() const { return m_Velocity; }

void Boid::setPosition(const glm::vec2& pos) { m_Position = pos; }
void Boid::setVelocity(const glm::vec2& vel) { m_Velocity = vel; }

void Boid::update(float /*deltaTime*/) {
    // TODO: implement behavior logic later
}

void Boid::render() const {
    // TBD
}

} // namespace Boids