#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
out vec2 fragTexCoord;
uniform mat4 mvp;

const float W = 800;
const float H = 500;

uniform int pass;

out vec2 samplePosition[25];

void main()
{
  fragTexCoord = vertexTexCoord;
  gl_Position = mvp * vec4(vertexPosition, 1);

  for (int i = 0; i < 25; i++) {
    float d = i - 12;
    samplePosition[i] = vertexTexCoord +
      (pass == 1 ? vec2(d / W, 0) : vec2(0, d / H));
  }
}
