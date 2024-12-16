#version 330 core
in vec2 vUv0;

uniform sampler2D spaceSkyTexture;
uniform sampler2D lightMapTexture;
uniform float intLuzAmb;

out vec4 fFragColor;

void main() {
    vec4 colorSky = vec4(texture(spaceSkyTexture, vUv0)); // Sacamos los colores de la textura del cielo.
    vec4 colorLight = vec4(texture(lightMapTexture, vUv0)); // Sacamos los colores de la textura del lightMap.
    vec4 color = mix(colorSky, colorLight, 0.5) * intLuzAmb; // Hacemos un mix de ellos.

    fFragColor = color; // Y se lo pasamos a fFragColor.
}