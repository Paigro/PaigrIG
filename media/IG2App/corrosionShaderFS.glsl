#version 330 core
in vec2 vUv0;

uniform sampler2D corrosionTexture;
uniform sampler2D dirtTexture;
uniform sampler2D bumpyMetalTexture;
uniform float flipping;

out vec4 fFragColor;

void main() {
    vec4 colorCorrosion = vec4(texture(corrosionTexture, vUv0)); // Sacamos los colores de la textura del corrosion.

    if(colorCorrosion.r > 0.6) { // Si esta muy oxidado (mucho rojo), descartamos esos vertices.
        discard;
    }

// Para saber si es la cara frontal o la trasera.
    bool frontFacing = (flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

    if(frontFacing) { // Si esta en el interior ponemos una textura,
        fFragColor = texture(bumpyMetalTexture, vUv0);
    } else { // sino la otra.
        fFragColor = texture(dirtTexture, vUv0);
    }
}