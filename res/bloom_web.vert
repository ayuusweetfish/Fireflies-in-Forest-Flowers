#version 100
precision mediump float;
attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;
varying vec2 fragTexCoord;
uniform mat4 mvp;

const float W = 800.;
const float H = 500.;

uniform int pass;

varying vec2 samplePosition[11];

void main()
{
  fragTexCoord = vertexTexCoord;
  gl_Position = mvp * vec4(vertexPosition, 1);

  for (int i = 0; i < 11; i++) {
    float d = float(i - 5);
    samplePosition[i] = vertexTexCoord +
      (pass == 1 ? vec2(d / W, 0) : vec2(0, d / H));
  }
}
