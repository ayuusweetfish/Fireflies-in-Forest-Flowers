#version 100
precision mediump float;
varying vec2 fragTexCoord;
varying vec4 fragColor;
#define outValue gl_FragColor

uniform vec2 spotCen;
uniform float spotRadius;
varying vec2 scrPos;

void main()
{
  float d = distance(spotCen, scrPos);
  float x = clamp((d - spotRadius) / 10.0, 0.0, 1.0) * 0.6;
  outValue = vec4(0.15, 0.15, 0.15, x);
  outValue *= fragColor;
}
