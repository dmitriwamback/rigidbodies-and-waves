//
//  vMain.glsl
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//
#version 410 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * model * vec4(vertex, 1.0);
    gl_PointSize = 10.0;
}
