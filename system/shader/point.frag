#version 300 es

precision mediump float;

in vec4 vertexOutColor;

out vec4 fragmentOutColor;

void main() {
  fragmentOutColor = vertexOutColor;
}
