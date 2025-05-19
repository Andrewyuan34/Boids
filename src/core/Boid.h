#pragma once
#include <glm/glm.hpp>
#include "ui/BoidsParams.h"

namespace Boids {

class Boid {
public:
    Boid(const glm::vec2& position, const glm::vec2& velocity);

    glm::vec2 getPosition() const;
    glm::vec2 getVelocity() const;

    void setPosition(const glm::vec2& pos);
    void setVelocity(const glm::vec2& vel);
    
    // apply force to boid
    void applyForce(const glm::vec2& force);

    // update boid's position and velocity
    void update(float deltaTime, const BoidsParams& params);

    void render() const;
private:
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    glm::vec2 m_Acceleration;
};

} // namespace Boids