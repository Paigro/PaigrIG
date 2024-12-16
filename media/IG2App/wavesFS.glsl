#version 330 core
in vec2 vUv0;

uniform sampler2D wavesTexture;

out vec4 fFragColor;

void main() {
    fFragColor = vec4(texture(wavesTexture, vUv0));
}