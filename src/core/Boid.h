#pragma once
#include <glm/glm.hpp>
#include "ui/BoidsParams.h"
#include <glm/gtc/quaternion.hpp>

namespace Boids {

class Boid {
public:
    Boid(const glm::vec3& position, const glm::vec3& velocity);

    glm::vec3 getPosition() const;
    glm::vec3 getVelocity() const;

    void setPosition(const glm::vec3& pos);
    void setVelocity(const glm::vec3& vel);
    
    // apply force to boid
    void applyForce(const glm::vec3& force);

    // update boid's position and velocity
    void update(float deltaTime, const BoidsParams& params);

    void render() const;
private:
    glm::vec3 m_Position;    
    glm::vec3 m_Velocity;    
    glm::vec3 m_Acceleration; 
    glm::quat m_Rotation;
    glm::vec3 m_Scale; 
};

} // namespace Boids