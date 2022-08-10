#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
out vec2 fragTexCoord;
uniform mat4 mvp;

const float W = 800.;
const float H = 500.;

uniform int pass;

out vec2 samplePosition[11];

void main()
{
  fragTexCoord = vertexTexCoord;
  gl_Position = mvp * vec4(vertexPosition, 1);

  vec2 s = vec2(1. / W, 1. / H) * sqrt(2.);
  if (pass == 1) s.x = -s.x;
  for (int i = 0; i < 11; i++) {
    samplePosition[i] = vertexTexCoord + float(i - 5) * s;
  }
}
