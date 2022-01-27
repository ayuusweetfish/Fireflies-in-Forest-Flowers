#version 100
precision mediump float;
uniform sampler2D texture0;
varying vec2 fragTexCoord;
#define outValue gl_FragColor

varying vec2 samplePosition[25];

vec4 premul(vec2 pos)
{
  vec4 value = texture2D(texture0, pos);
  value.rgb *= value.a;
  return value;
}

void main()
{
  vec4 blurA = vec4(0);
  blurA += 0.1611802577972412 * premul(samplePosition[12]);
  blurA += 0.14878177642822266 * (premul(samplePosition[11]) + premul(samplePosition[13]));
  blurA += 0.11689996719360352 * (premul(samplePosition[10]) + premul(samplePosition[14]));
  blurA += 0.07793331146240234 * (premul(samplePosition[9]) + premul(samplePosition[15]));
  blurA += 0.04383748769760132 * (premul(samplePosition[8]) + premul(samplePosition[16]));
  blurA += 0.020629405975341797 * (premul(samplePosition[7]) + premul(samplePosition[17]));

  outValue = blurA;
  if (outValue.a != 0.0) outValue.rgb /= outValue.a;
}
