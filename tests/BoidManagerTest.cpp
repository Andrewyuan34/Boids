#include <gtest/gtest.h>
#include "core/BoidManager.h"
#include "ui/BoidsParams.h"
#include <glm/gtx/norm.hpp>

namespace Boids {
namespace Test {

class BoidManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set default parameters
        params.boidCount = 3;  // Use fewer boids for easier testing
        params.maxSpeed = 0.5f;
        params.maxForce = 0.03f;
        params.separationRadius = 1.0f;
        params.alignmentRadius = 1.0f;
        params.cohesionRadius = 1.0f;
        params.boundaryMin = -1.0f;
        params.boundaryMax = 1.0f;
        params.boundaryForceMax = 0.1f;
    }

    BoidsParams params;
    BoidManager manager;
};

// Test initialization
TEST_F(BoidManagerTest, Initialize) {
    manager.initialize(params);
    const auto& boids = manager.getBoids();

    // 1. Verify the number of boids
    EXPECT_EQ(boids.size(), params.boidCount);

    // 2. Verify the initial state of each boid
    for (const auto& boid : boids) {
        // 2.1 Verify the position is within the boundary range
        glm::vec3 pos = boid->getPosition();
        EXPECT_GE(pos.x, params.boundaryMin);
        EXPECT_LE(pos.x, params.boundaryMax);
        EXPECT_GE(pos.y, params.boundaryMin);
        EXPECT_LE(pos.y, params.boundaryMax);
        EXPECT_GE(pos.z, params.boundaryMin);
        EXPECT_LE(pos.z, params.boundaryMax);

        // 2.2 Verify the velocity is within the maximum speed limit
        glm::vec3 vel = boid->getVelocity();
        float speed = glm::length(vel);
        EXPECT_LE(speed, params.maxSpeed);

        // 2.3 Verify the boid state is valid
        EXPECT_TRUE(boid != nullptr);
        EXPECT_TRUE(std::isfinite(pos.x) && std::isfinite(pos.y) && std::isfinite(pos.z));  // Check each component
        EXPECT_TRUE(std::isfinite(vel.x) && std::isfinite(vel.y) && std::isfinite(vel.z));  // Check each component
    }

    // 3. Verify the initial distance between boids is reasonable (not too close)
    for (size_t i = 0; i < boids.size(); ++i) {
        for (size_t j = i + 1; j < boids.size(); ++j) {
            glm::vec3 diff = boids[i]->getPosition() - boids[j]->getPosition();
            float dist = glm::length(diff);
            EXPECT_GT(dist, 0.01f);  // Ensure there is a minimum distance between boids
        }
    }
}

TEST_F(BoidManagerTest, ComputeSeparation) {
    manager.initialize(params);
    const auto& boids = manager.getBoids();

    boids[0]->setPosition(glm::vec3(0.0f));
    boids[1]->setPosition(glm::vec3(0.1f, 0.0f, 0.0f));

    glm::vec3 force = manager.computeSeparation(*boids[0], params);

    // Verify the force is in the correct direction
    EXPECT_LT(force.x, 0.0f);  // the x direction should be negative (away from)

    // Verify the force magnitude is within a reasonable range
    float forceMagnitude = glm::length(force);
    EXPECT_GT(forceMagnitude, 0.0f);  // The force should be greater than 0
    EXPECT_LT(forceMagnitude, params.maxForce+0.05);  // The force should not exceed the maximum value + 5%
}

// Test compute alignment
TEST_F(BoidManagerTest, ComputeAlignment) {
    manager.initialize(params);
    const auto& boids = manager.getBoids();

    // Set the initial velocities of two boids
    boids[0]->setVelocity(glm::vec3(0.1f, 0.0f, 0.0f));
    boids[1]->setVelocity(glm::vec3(0.2f, 0.0f, 0.0f));
    boids[1]->setPosition(glm::vec3(0.5f, 0.0f, 0.0f));

    glm::vec3 force = manager.computeAlignment(*boids[0], params);

    // The alignment force should point towards the average velocity direction
    EXPECT_GT(force.x, 0.0f);
}

// Test compute boundary force
TEST_F(BoidManagerTest, ComputeBoundaryForce) {
    glm::vec3 pos(0.9f, 0.0f, 0.0f);  // Near upper boundary
    float buffer = 0.2f;

    glm::vec3 force = manager.computeBoundaryForce(pos, params.boundaryMin, params.boundaryMax, buffer, params.boundaryForceMax);

    // Verify the force direction (should point towards the inside) and magnitude (proportional to the distance)
    float expectedForce = -params.boundaryForceMax * 0.5f;  // The distance is half of the buffer, so the force is half
    EXPECT_NEAR(force.x, expectedForce, params.boundaryForceMax * 0.1f);
    EXPECT_NEAR(force.y, 0.0f, params.boundaryForceMax * 0.1f);
    EXPECT_NEAR(force.z, 0.0f, params.boundaryForceMax * 0.1f);
}

// Test compute cohesion
TEST_F(BoidManagerTest, ComputeCohesion) {
    manager.initialize(params);
    const auto& boids = manager.getBoids();

    // Set positions for two boids
    boids[0]->setPosition(glm::vec3(0.0f));
    boids[1]->setPosition(glm::vec3(0.5f, 0.0f, 0.0f));

    glm::vec3 force = manager.computeCohesion(*boids[0], params);

    // The cohesion force should point towards the group center
    EXPECT_GT(force.x, 0.0f);
}

} // namespace Test
} // namespace Boids 