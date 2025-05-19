#pragma once
#include <glm/glm.hpp>

namespace Boids {

class Boid {
public:
    Boid(const glm::vec2& position, const glm::vec2& velocity);

    glm::vec2 getPosition() const;
    glm::vec2 getVelocity() const;

    void setPosition(const glm::vec2& pos);
    void setVelocity(const glm::vec2& vel);

    // up
    void update(float deltaTime);

    void render() const;
private:
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
};

} // namespace Boids