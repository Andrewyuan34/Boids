#pragma once

#include "ui/BoidsParams.h"

// A base class for all entities in the "Boids"
class Entity {
   public:
    virtual void update(float deltaTime) = 0;
    virtual void render() const = 0;
    virtual ~Entity() = default;
};