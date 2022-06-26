#version 100
precision mediump float;
varying vec2 fragTexCoord;
varying vec4 fragColor;
#define outValue gl_FragColor

uniform vec2 spotCen[2];
uniform float spotRadius[2];
varying vec2 scrPos;

void main()
{
  float x = 1.0;
  for (int i = 0; i < 2; i++) if (spotRadius[i] > 0.0) {
    float d = distance(spotCen[i], scrPos);
    x = min(x, clamp((d - spotRadius[i]) / 10.0, 0.0, 1.0));
  }
  outValue = vec4(0.15, 0.15, 0.15, x * 0.6);
  outValue *= fragColor;
}
