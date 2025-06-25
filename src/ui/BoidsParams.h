#pragma once

struct BoidsParams {
    // Global simulation parameters
    int boidCount = 50;
    float worldSize = 500.0f;
    float simulationSpeed = 1.0f;

    // Movement parameters
    float maxSpeed = 0.5f;
    float maxForce = 0.03f;

    // Behavior weights
    float alignmentWeight = 0.3f;
    float separationWeight = 0.38f;
    float cohesionWeight = 0.32f;
    float boundaryWeight = 0.1f;

    // Behavior radius
    float separationRadius = 25.0f;
    float alignmentRadius = 25.0f;
    float cohesionRadius = 25.0f;

    // Boundary parameters
    float boundaryMin = -1.0f;
    float boundaryMax = 1.0f;
    float boundaryForceMax = 0.1f;

    // Static access method
    static BoidsParams& get() {
        static BoidsParams instance;
        return instance;
    }

    static const BoidsParams& getConst() { return get(); }

    // Reset to default values
    static void reset() { get() = BoidsParams{}; }
};