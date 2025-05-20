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
    float alignmentWeight = 0.35f;
    float separationWeight = 0.37f;
    float cohesionWeight = 0.32f;
    float boundaryWeight = 0.1f;

    // Behavior radii
    float separationRadius = 5.0f;
    float alignmentRadius = 5.0f;
    float cohesionRadius = 5.0f;

	// Boundary parameters
	float boundaryMin = -1.0f;
	float boundaryMax = 1.0f;
	float boundaryForceMax = 0.1f;
};