#pragma once

struct BoidsParams {
    // Global simulation parameters
    int boidCount = 100;
    float worldSize = 500.0f;
    float simulationSpeed = 1.0f;

    // Movement parameters
    float maxSpeed = 0.3f;
    float maxForce = 0.05f;

    // Behavior weights
    float alignmentWeight = 1.0f;
    float separationWeight = 1.5f;
    float cohesionWeight = 1.0f;

    // Behavior radii
    float separationRadius = 25.0f;
    float alignmentRadius = 50.0f;
    float cohesionRadius = 50.0f;
};