#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 outValue;

uniform vec2 spotCen;
uniform float spotRadius;
in vec2 scrPos;

void main()
{
  float d = distance(spotCen, scrPos);
  float x = clamp((d - spotRadius) / 10.0, 0.0, 1.0) * 0.6;
  outValue = vec4(0.15, 0.15, 0.15, x);
  outValue *= fragColor;
}
