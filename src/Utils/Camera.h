#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Boids {
namespace Utils {

class Camera {
   public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    // Getters
    glm::vec3 getPosition() const;
    glm::quat getOrientation() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    float getFOV() const;

    // Setters
    void setPosition(const glm::vec3& position);
    void setOrientation(const glm::quat& orientation);
    void setFOV(float fov);
    void setAspectRatio(float aspect);
    void setClipPlanes(float nearPlane, float farPlane);

    // Movement
    void move(const glm::vec3& offset);
    void rotate(const glm::vec3& eulerAngles);  // input in degrees
    void smoothRotate(const glm::quat& targetOrientation, float smoothFactor);

   private:
    glm::vec3 position;
    glm::quat orientation;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    void updateViewMatrix();
    void updateProjectionMatrix();

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

}  // namespace Utils
}  // namespace Boids