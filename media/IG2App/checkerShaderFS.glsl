#version 330 core
in vec2 vUv0;

uniform sampler2D checkerTexture;
uniform sampler2D corrosionTexture;
uniform sampler2D bumpyMetalTexture;

out vec4 fFragColor;

void main() {
    vec4 colorChecker = vec4(texture(checkerTexture, vUv0)); // Sacamos los colores de la textura del checker.
    vec4 colorCorrosion = vec4(texture(corrosionTexture, vUv0)); // Sacamos los colores de la textura del corrosion.
    vec4 colorMetal = vec4(texture(bumpyMetalTexture, vUv0)); // Sacamos los colores de la textura del metal.

    float isBlack = colorChecker.r + colorChecker.g + colorChecker.b;

    if(isBlack == 0.0) { // Si la suma del rgb del checker es negro (0.0) ponemos una textura.
        fFragColor = colorCorrosion;
    } else { // Sino la otra.
        fFragColor = colorMetal;
    }
}