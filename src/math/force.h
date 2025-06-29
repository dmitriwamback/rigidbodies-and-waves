//
//  force.h
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//

#ifndef force_h
#define force_h

#define g 9.81f

float DegreesToRadians(float degrees) {
    return degrees * 3.14159265358979f / 180.0f;
}

float RadiansToDegrees(float radians) {
    return radians * 180.0f / 3.14159265358979f;
}


struct Force {
    glm::vec3 direction;
    float newtons;
};

Force ComputeNormalForceFromPlane(float mass, glm::vec3 rotation) {
    
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 surfaceNormal = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(up, 0.0)));
    
    float magnitude = glm::dot(surfaceNormal, up) * mass * g;
    
    Force normalForce{};
    normalForce.direction = surfaceNormal;
    normalForce.newtons = glm::max(magnitude, 0.0f);
    
    return normalForce;
}

Force ComputeGravitationalForceFromPlane(float mass, glm::vec3 rotation) {
    glm::vec3 gravity = glm::vec3(0, -1, 0);
    glm::vec3 localUp = glm::vec3(0, 1, 0);

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));

    glm::vec3 surfaceNormal = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(localUp, 0.0)));
    glm::vec3 gravityForce = mass * g * gravity;
    glm::vec3 forcePerpendicular = glm::dot(gravityForce, surfaceNormal) * surfaceNormal;
    glm::vec3 forceAlongPlane = gravityForce - forcePerpendicular;

    Force result;
    result.direction = glm::normalize(forceAlongPlane);
    result.newtons = glm::length(forceAlongPlane);
    
    if (glm::dot(surfaceNormal, gravity) >= 0) {
        result.direction = gravity;
        result.newtons = g * mass;
    }
    else {
        result.direction = glm::normalize(forceAlongPlane);
        result.newtons = glm::length(forceAlongPlane);
    }
    
    return result;
}

#endif /* force_h */
