#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Entity.h"
#include "ui/BoidsParams.h"

// To be removed to other folder later
namespace Boids {

struct Transform {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};

class Boid : public Entity {
   public:
    Boid(const glm::vec3& position, const glm::vec3& velocity);
    ~Boid() = default;

    // override Entity's update function
    void update(float deltaTime) final;
    void render() const final;

    // Boid's own update function(to be removed later) maybe set BoidsParam as a global/static data?
    void update(float deltaTime, const BoidsParams& params);

    glm::vec3 getPosition() const;
    glm::vec3 getVelocity() const;

    void setPosition(const glm::vec3& pos);
    void setVelocity(const glm::vec3& vel);

    // apply force to boid
    void applyForce(const glm::vec3& force);

   private:
    Transform m_Transform;
};

}  // namespace Boids