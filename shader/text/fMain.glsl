//
//  fMain.glsl
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//
#version 410 core

out vec4 fragc;
in vec2 uv;
uniform sampler2D text;

uniform vec3 color;

void main() {
    vec4 sampled = vec4(color, texture(text, uv).r);
    fragc = sampled;
}
