#define GLM_ENABLE_EXPERIMENTAL
#include "Camera.h"

namespace Boids {
namespace Utils {

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : position(0.0f, 0.0f, 3.0f),
      orientation(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f))),
      fov(fov),
      aspectRatio(aspectRatio),
      nearPlane(nearPlane),
      farPlane(farPlane) {
    updateViewMatrix();
    updateProjectionMatrix();
}

glm::vec3 Camera::getPosition() const { return position; }
glm::quat Camera::getOrientation() const { return orientation; }
float Camera::getFOV() const { return fov; }

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
    updateViewMatrix();
}

void Camera::setOrientation(const glm::quat& orient) {
    orientation = orient;
    updateViewMatrix();
}

void Camera::setFOV(float f) {
    fov = f;
    updateProjectionMatrix();
}

void Camera::setAspectRatio(float aspect) {
    aspectRatio = aspect;
    updateProjectionMatrix();
}

void Camera::setClipPlanes(float nearP, float farP) {
    nearPlane = nearP;
    farPlane = farP;
    updateProjectionMatrix();
}

void Camera::move(const glm::vec3& offset) {
    position += orientation * offset;
    updateViewMatrix();
}

void Camera::rotate(const glm::vec3& eulerDegrees) {
    glm::vec3 eulerRadians = glm::radians(eulerDegrees);
    glm::quat delta = glm::quat(eulerRadians);
    orientation = glm::normalize(delta * orientation);
    updateViewMatrix();
}

void Camera::smoothRotate(const glm::quat& targetOrientation, float smoothFactor) {
    orientation = glm::slerp(orientation, targetOrientation, smoothFactor);
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix() const { return viewMatrix; }

glm::mat4 Camera::getProjectionMatrix() const { return projectionMatrix; }

void Camera::updateViewMatrix() {
    glm::mat4 rotation = glm::toMat4(glm::conjugate(orientation));
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), -position);
    viewMatrix = rotation * translation;
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

}  // namespace Utils
}  // namespace Boids
