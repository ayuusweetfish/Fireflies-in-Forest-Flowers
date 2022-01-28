#version 100
precision mediump float;
uniform sampler2D texture0;
varying vec2 fragTexCoord;
#define outValue gl_FragColor

varying vec2 samplePosition[11];

vec4 premul(vec2 pos)
{
  vec4 value = texture2D(texture0, pos);
  value.rgb *= value.a;
  return value;
}

void main()
{
  vec4 blurA = vec4(0);
  blurA += 0.15497842 * (premul(samplePosition[5]));
  blurA += 0.14464653 * (premul(samplePosition[4]) + premul(samplePosition[6]));
  blurA += 0.11752530 * (premul(samplePosition[3]) + premul(samplePosition[7]));
  blurA += 0.08295904 * (premul(samplePosition[2]) + premul(samplePosition[8]));
  blurA += 0.05069719 * (premul(samplePosition[1]) + premul(samplePosition[9]));
  blurA += 0.02668273 * (premul(samplePosition[0]) + premul(samplePosition[10]));

  outValue = blurA;
  if (outValue.a != 0.0) outValue.rgb /= outValue.a;
  if (samplePosition[0].x == fragTexCoord.x) outValue.a = pow(outValue.a, 0.8);
}
