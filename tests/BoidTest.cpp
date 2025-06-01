#include <gtest/gtest.h>

#include <glm/gtx/norm.hpp>

#include "core/Boid.h"
#include "ui/BoidsParams.h"

namespace Boids {
namespace Test {

class BoidTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Set default parameters
        params.boidCount = 50;
        params.maxSpeed = 0.5f;
        params.maxForce = 0.03f;
    }

    BoidsParams params;
};

// Test constructor and properties
TEST_F(BoidTest, ConstructorAndProperties) {
    glm::vec3 pos(1.0f, 2.0f, 3.0f);
    glm::vec3 vel(0.1f, 0.2f, 0.3f);
    Boid boid(pos, vel);

    EXPECT_FLOAT_EQ(boid.getPosition().x, pos.x);
    EXPECT_FLOAT_EQ(boid.getPosition().y, pos.y);
    EXPECT_FLOAT_EQ(boid.getPosition().z, pos.z);
    EXPECT_FLOAT_EQ(boid.getVelocity().x, vel.x);
    EXPECT_FLOAT_EQ(boid.getVelocity().y, vel.y);
    EXPECT_FLOAT_EQ(boid.getVelocity().z, vel.z);
}

// Test force application
TEST_F(BoidTest, ApplyForce) {
    glm::vec3 pos(0.0f);
    glm::vec3 vel(0.0f);
    Boid boid(pos, vel);

    glm::vec3 force(0.1f, 0.2f, 0.3f);
    boid.applyForce(force);
    boid.update(1.0f, params);

    // The velocity should equal the force (since initial velocity is 0)
    EXPECT_NEAR(glm::length(boid.getVelocity()), glm::length(force), 0.0001f);
}

// Test maximum speed limit
TEST_F(BoidTest, MaxSpeedLimit) {
    glm::vec3 pos(0.0f);
    glm::vec3 vel(0.0f);
    Boid boid(pos, vel);

    // Apply a force that exceeds the maximum speed
    glm::vec3 force(params.maxSpeed * 2.0f, 0.0f, 0.0f);
    boid.applyForce(force);
    boid.update(1.0f, params);

    // The velocity should be limited to the maximum speed
    EXPECT_NEAR(glm::length(boid.getVelocity()), params.maxSpeed, 0.0001f);
}

// Test position update
TEST_F(BoidTest, PositionUpdate) {
    glm::vec3 pos(0.0f);
    glm::vec3 vel(0.1f, 0.2f, 0.3f);
    Boid boid(pos, vel);

    float deltaTime = 1.0f;
    boid.update(deltaTime, params);

    // The new position should be the initial position plus the velocity times the time
    glm::vec3 expectedPos = pos + vel * deltaTime;
    EXPECT_NEAR(glm::length(boid.getPosition() - expectedPos), 0.0f, 0.0001f);
}

}  // namespace Test
}  // namespace Boids