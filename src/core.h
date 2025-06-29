//
//  core.h
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//

#ifndef core_h
#define core_h

#include <GL/glew.h>
#include <glfw3.h>

GLFWwindow* window;
float debugTime;

#include <fstream>
#include <sstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "object/shader.h"
#include "object/vertex.h"
#include "math/force.h"
#include "object/gameobjects/debug_triangle.h"

void initialize() {
    glfwInit();
        
#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    window = glfwCreateWindow(1200, 800, "Rigidbodies", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    Shader shader = Shader::Create("/Users/dmitriwamback/Documents/Projects/rigidbodies-and-waves/rigidbodies-and-waves/shader/debug2D");
    Debug2DTriangle triangle = Debug2DTriangle::Create(2.0f, 2.0f);
    glm::mat4 testProjection = glm::perspective(glm::radians(90.0f), 1200.0f/800.0f, 1000.0f, 0.1f);
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        testProjection = glm::perspective(glm::radians(90.0f), (float)width/(float)height, 1000.0f, 0.1f);
        shader.Use();
        shader.SetMatrix4("projection", testProjection);
        
        triangle.rotation += glm::vec3(0.0f, 0.0f, 0.5f);
        triangle.Render(shader);
        
        debugTime += 0.01f;
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

#endif /* core_h */
