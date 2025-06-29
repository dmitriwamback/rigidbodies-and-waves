//
//  vMain.glsl
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//
#version 410 core

layout (location = 0) in vec4 vertex;

out vec2 uv;
uniform mat4 projection;

void main() {
    uv = vertex.zw;
    uv.y = 1 - uv.y;
    gl_Position = projection * vec4(vertex.xy, -1.0, 1.0);
}

