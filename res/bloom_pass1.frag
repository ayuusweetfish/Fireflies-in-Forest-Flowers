#version 330

uniform sampler2D texture0;
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 outValue;

const float W = 800;
const float H = 500;

uniform int pass;

vec4 texturePremultipliedAlpha(vec2 pos)
{
  vec4 value = textureLod(texture0, pos, 0);
  value.rgb *= value.a;
  return value;
}

vec2 move(float x)
{
  return (pass == 1 ? vec2(x / W, 0) : vec2(0, x / H));
}

void main()
{
  float kernelA[8] = float[](
    0.20947265625, 0.18328857421875, 0.1221923828125, 0.06109619140625, 0.022216796875, 0.00555419921875, 0.0008544921875, 6.103515625e-05
  );
  vec4 blurA = vec4(0);
  for (int i = -7; i <= 7; i++)
    blurA += kernelA[abs(i)] * texturePremultipliedAlpha(fragTexCoord + move(i));
  outValue = blurA;
  if (outValue.a != 0) outValue.rgb /= outValue.a;
  //outValue.rgb = vec3(outValue.a); outValue.a = 1;
  //outValue.a = sqrt(outValue.a);
  //outValue.a = 0.5;
  //outValue = vec4(1,1,1,0.875);
  //outValue.rgb = vec3(outValue.a); outValue.a = 1;
  //outValue.rgb = vec3(texture(texture0, fragTexCoord).a); outValue.a = 1;
}
