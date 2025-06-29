#include <gtest/gtest.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/Camera.h"

namespace Boids {
namespace Tests {

class CameraTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Setup code that will be called before each test
    }

    void TearDown() override {
        // Cleanup code that will be called after each test
    }
};

}  // namespace Tests
}  // namespace Boids