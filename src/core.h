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

#include <ft2build.h>
#include FT_FREETYPE_H

GLFWwindow* window;
float debugTime;
FT_Face face;

#define THETA_UNICODE 0x0398

#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "object/shader.h"

glm::mat4 testProjection;
Shader triangleShader, textShader;

#include "object/text.h"
#include "object/vertex.h"
#include "math/force.h"
#include "object/gameobjects/physics_object_2d.h"
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
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }
    
    if (FT_New_Face(ft, "/Users/dmitriwamback/Documents/Projects/rigidbodies-and-waves/rigidbodies-and-waves/fonts/computer-modern/cmunci.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    
    triangleShader = Shader::Create("/Users/dmitriwamback/Documents/Projects/rigidbodies-and-waves/rigidbodies-and-waves/shader/debug2D");
    textShader = Shader::Create("/Users/dmitriwamback/Documents/Projects/rigidbodies-and-waves/rigidbodies-and-waves/shader/text");
    
    PhysicsObject2D* triangle = Debug2DTriangle::Create(5.0f, 2.0f);
    
    testProjection = glm::perspective(glm::radians(90.0f), 1200.0f/800.0f, 1000.0f, 0.1f);
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        testProjection = glm::perspective(glm::radians(90.0f), (float)width/(float)height, 1000.0f, 0.1f);
        triangleShader.Use();
        triangleShader.SetMatrix4("projection", testProjection);
        triangle->Render(triangleShader);
        
        debugTime += 0.01f;
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

#endif /* core_h */
