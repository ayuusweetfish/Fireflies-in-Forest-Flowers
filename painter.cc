#include "main.hh"
using namespace rl;

static Font font;

void painter::init()
{
  font = LoadFont("res/Imprima.ttf");
}

void painter::text(
  const char *s, int size,
  vec2 pos, vec2 anchor, float alpha)
{
  Vector2 dims = MeasureTextEx(font, s, size, 0);
  DrawTextEx(
    font, s,
    (Vector2){pos.x - dims.x * anchor.x, pos.y - dims.y * anchor.y},
    size, 0,
    (Color){255, 255, 255, (unsigned char)(255 * alpha)}
  );
}
