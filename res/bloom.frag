#version 330

uniform sampler2D texture0;
in vec2 fragTexCoord;
out vec4 outValue;

const float W = 800;
const float H = 500;

uniform int pass;

in vec2 samplePosition[25];

vec4 texturePremultipliedAlpha(vec2 pos)
{
  vec4 value = textureLod(texture0, pos, 0);
  value.rgb *= value.a;
  return value;
}

void main()
{
  float kernelA[] = float[](
    0.1611802577972412, 0.14878177642822266, 0.11689996719360352, 0.07793331146240234, 0.04383748769760132, 0.020629405975341797, 0.008022546768188477, 0.002533435821533203, 0.0006333589553833008, 0.00012063980102539062, 1.6450881958007812e-05, 1.430511474609375e-06, 5.960464477539063e-08
  );
  vec4 blurA = vec4(0);
  for (int i = 0; i < 25; i++)
    blurA += kernelA[abs(i - 12)] * texturePremultipliedAlpha(samplePosition[i]);

  outValue = blurA;// * 0.5 + blurB * 0.5;
  if (outValue.a != 0) outValue.rgb /= outValue.a;
  if (pass == 2) outValue.a = pow(outValue.a, 0.75);
}
