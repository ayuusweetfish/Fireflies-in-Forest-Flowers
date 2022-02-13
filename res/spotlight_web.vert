#version 100
precision mediump float;
attribute vec3 vertexPosition;
attribute vec4 vertexColor;
varying vec4 fragColor;
uniform mat4 mvp;

const float W = 800.;
const float H = 500.;

varying vec2 scrPos;

void main()
{
  fragColor = vertexColor;
  gl_Position = mvp * vec4(vertexPosition, 1);

  scrPos = vec2(
    (1.0 + gl_Position.x) / 2.0 * W,
    (1.0 - gl_Position.y) / 2.0 * H
  );
}
