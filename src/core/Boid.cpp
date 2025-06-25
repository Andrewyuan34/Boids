#include "Boid.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Boids {

Boid::Boid(const glm::vec3& position, const glm::vec3& velocity) {
    // Initialize transform
    m_Transform.position = position;
    m_Transform.velocity = velocity;
    m_Transform.acceleration = glm::vec3(0.0f);
    m_Transform.scale = glm::vec3(0.1f);  // Set a default scale

    // Initialize rotation to face velocity direction
    if (glm::length(velocity) > 0.0f) {
        m_Transform.rotation =
            glm::quatLookAt(glm::normalize(velocity), glm::vec3(0.0f, 0.0f, 1.0f));
    }
}

glm::vec3 Boid::getPosition() const { return m_Transform.position; }
glm::vec3 Boid::getVelocity() const { return m_Transform.velocity; }

void Boid::setPosition(const glm::vec3& pos) { m_Transform.position = pos; }
void Boid::setVelocity(const glm::vec3& vel) { m_Transform.velocity = vel; }

void Boid::applyForce(const glm::vec3& force) { m_Transform.acceleration += force; }

void Boid::update(float deltaTime) {
    m_Transform.velocity += m_Transform.acceleration;
    m_Transform.position += m_Transform.velocity * deltaTime;
    m_Transform.acceleration = glm::vec3(0.0f);

    // no need to update rotation for now
    // if (glm::length(m_Transform.velocity) > 0.001f) {
    //   m_Transform.rotation = glm::quatLookAt(glm::normalize(m_Transform.velocity),
    //   glm::vec3(0.0f, 1.0f, 0.0f));
    //}
}

void Boid::update(float deltaTime, const BoidsParams& params) {
    // call base update
    update(deltaTime);

    // apply Boids's own limit
    if (glm::length(m_Transform.velocity) > params.maxSpeed) {
        m_Transform.velocity = glm::normalize(m_Transform.velocity) * params.maxSpeed;
    }
}

void Boid::render() const {
    // For now, just render a simple triangle
    glBegin(GL_TRIANGLES);
    // Set color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw a triangle
    glVertex3f(m_Transform.position.x, m_Transform.position.y, m_Transform.position.z);
    glVertex3f(m_Transform.position.x + 0.1f, m_Transform.position.y - 0.1f,
               m_Transform.position.z);
    glVertex3f(m_Transform.position.x - 0.1f, m_Transform.position.y - 0.1f,
               m_Transform.position.z);
    glEnd();
}

}  // namespace Boids