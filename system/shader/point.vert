#version 300 es

precision mediump float;

layout(location = 0) in vec2 vertexPosition;

out vec4 vertexOutColor;

uniform float time;
uniform vec2 position;
uniform vec3 color;
uniform float size;

void main() {
  gl_Position.xy = position.xy;
  gl_Position.zw = vec2 (0.0, 1.0);
  gl_PointSize = size;
  vertexOutColor = vec4(color, 1.0);
}


