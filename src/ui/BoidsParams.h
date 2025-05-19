#pragma once

struct BoidsParams {
        // 全局仿真参数
    int boidCount = 100;
    float worldSize = 500.0f;
    float simulationSpeed = 1.0f;

    // Movement parameters
    float maxSpeed = 2.0f;
    float maxForce = 0.05f;

    // Behavior weights
    float alignmentWeight = 1.0f;
    float separationWeight = 1.5f;
    float cohesionWeight = 1.0f;
};