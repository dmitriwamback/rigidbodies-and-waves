//
//  fMain.glsl
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//
#version 410 core

out vec4 fragc;

uniform vec3 color;

void main() {
    fragc = vec4(color, 1.0);
}
