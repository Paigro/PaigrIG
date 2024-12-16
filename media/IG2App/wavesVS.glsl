#version 330 core

in vec4 vertex;
in vec2 uv0;

uniform mat4 modelViewProjMat;
uniform float sinTime;
uniform vec2 center;

out vec2 vUv0;

void main() {
    vUv0 = uv0;
    // Auxiliar para guardar los vertices.
    vec4 vertexCoord = vertex;

    float distanceToCenter = distance(vec2(vertexCoord.x, vertexCoord.z), center);

    float a = 40;
    float b = 5;

    vertexCoord.y += sin(vertexCoord.x + (sinTime * a)) * b + sin(vertexCoord.z + (distanceToCenter) + (sinTime * a)) * b;

    gl_Position = modelViewProjMat * vertexCoord;
}